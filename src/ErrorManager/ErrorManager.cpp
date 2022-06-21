
#include <ErrorManager.h>
#include <Arduino.h>
#include <PubSubClient.h>
#include <EEPROM.h>
#include <settings.h>
#include "data.h"
#include "webserver.h"

boolean ErrorManager::Begin() {
  NbErrorWifi 		= 0;
  NbErrorMqtt 		= 0;
  NbErrorCapteur 	= 0;
  NbErrorNTP		= 0;
  NbErrorSD			= 0;
  NbReboot          = 0;

  TimeWifi = TimeMqtt = TimeCapteur = TimeNTP = TimeSD = 0;	
	
  CompteurHandle   = 0;	
  return true;
}

void ErrorManager::SetErrorWifi() {
  Serial.print("Erreur Wifi : ");
  NbErrorWifi++;
  Serial.println(NbErrorWifi);
  if (TimeWifi == 0) TimeWifi = millis();
  CompteurHandle = 0;
}

void ErrorManager::SetErrorMqtt() {
  if (WifiActif) {	
    NbErrorMqtt++;
    Serial.print("Erreur Mqtt : ");
    Serial.println(NbErrorMqtt);
    if (TimeMqtt == 0) TimeMqtt = millis();
	CompteurHandle = 0;
  }
}

void ErrorManager::SetErrorCapteur() {
  NbErrorCapteur++;
  Serial.print("Erreur Capteur : ");
  Serial.println(NbErrorCapteur);
  if (TimeCapteur == 0) TimeCapteur = millis();
  CompteurHandle = 0;
}

void ErrorManager::SetErrorNTP() {
  NbErrorNTP++;
}

void ErrorManager::SetErrorSD() {
  NbErrorSD++;
}

void ErrorManager::SetWifiActif() {
  WifiActif = true;	
  TimeWifi  = 0;
  Serial.println("Wifi Actif");
}
   
void ErrorManager::SetMqttActif() {
  MqttActif = true;	
  TimeMqtt  = 0;
  Serial.println("Mqtt Actif");
}

void ErrorManager::Handle() {
  char tmpmsg[50];
  char msgTopic[50];

// Gestion des erreurs sur les capteurs
	
  if ((TimeCapteur != 0) && ((millis() -  TimeCapteur) > TIME_ERROR_CAPTEUR)) {
	strcpy(msgTopic,TOPIC);
    strcat(msgTopic,data.CapteurID);
    strcat(msgTopic,ERROR_CAPTEUR_TOPIC);

    if (NbErrorCapteur > 10) {
       Serial.println("*********** Capteur Erreur **************");

       if ((webserver.wificonnected) && (webserver.mqtt_enable)) {
		 if (ResetCapteur) NbErrorCapteur = 99;  
		 sprintf (tmpmsg, "%i", NbErrorCapteur);
         if (client.connected())  client.publish(msgTopic, tmpmsg);
       }	
       
	   TimeCapteur = millis();	 
       NbErrorCapteur = 0;	
       if (ResetCapteur) {
         Serial.println("Reset..");
         ESP.restart();    
//         ESP.reset();  
	   }
	   else {
	     ResetCapteur = true;
	   } 
    }
	else {
      if (client.connected())  client.publish(msgTopic, "0");
	  NbErrorCapteur = 0;
      TimeCapteur = 0;
      ResetCapteur = false;	  
	}	
  }
  else {
	strcpy(msgTopic,TOPIC);
    strcat(msgTopic,data.CapteurID);
    strcat(msgTopic,ERROR_CAPTEUR_TOPIC);
	
    if (client.connected())  client.publish(msgTopic, "0");
  }	  

// Gestion des erreurs sur la liaison MQTT

  if ((TimeMqtt != 0) && ((millis() -  TimeMqtt) > TIME_ERROR_MQTT)) {
    if (NbErrorMqtt > 10) {
       Serial.println("************* Mqtt Erreur ***************");
     
	   TimeMqtt = millis();	 
       NbErrorMqtt = 0;	
       if (ResetMqtt) {
		 Reboot();  
	   }
	   else {
	     ResetMqtt = true;
	   } 
    }
	else {
	  NbErrorMqtt = 0;
      TimeMqtt = 0;
      ResetMqtt = false;	  
	}	
  }
  
  
// Gestion des erreurs sur la connection Wifi

  if ((TimeWifi != 0) && ((millis() -  TimeWifi) > TIME_ERROR_WIFI)) {
    if (NbErrorWifi > 10) {
       Serial.println("************* Wifi Erreur **************");
     
	     TimeWifi = millis();	 
       NbErrorWifi = 0;	
       if (ResetWifi) {
		     Reboot();  
	     }
	     else {
	       ResetWifi = true;
	     } 
    }
	  else {
	    NbErrorWifi = 0;
      TimeWifi = 0;
      ResetWifi = false;	  
	  }	
  }
  CompteurHandle++;
  
  if ((WifiActif) && (MqttActif) && (CompteurHandle > 100)) {
    SaveEeprom(0);	
  }
}


void ErrorManager::Reboot() {
  if (nbreboot < 5) {	
    SaveEeprom(nbreboot);	
    Serial.println("Reset..");
    ESP.restart();    
  }
}
	
void ErrorManager::SaveEeprom(int Nbreboot) {
  data.SaveEepromNbreboot(Nbreboot);
}
