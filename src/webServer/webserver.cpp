/* webserver -- 
 *
 * Copyright 2020 Jean-philippe GOI
 * 
 */

/*********************************************************************************/
/*                                                                               */
/*                           Webserver                                           */
/*                                                                               */
/*  version    Date        Description                                           */
/*    1.0      28/12/20                                                          */
/*    1.0.1    21/01/21    Modif gestion eeprom                                  */
/*                                                                               */
/*																																							 */
/*********************************************************************************/

#include <webserver.h>
#include <Arduino.h>

#include "settings.h"
#include "data.h"

#include <ESP8266WebServer.h>
#include <PubSubClient.h>

#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

ESP8266WiFiMulti 	wifiMulti;
WebServer 				webserver;

/*   Gestion de la date et de l'heure */

#include <TimeLib.h>
#include <NtpClientLib.h>

#include <time.h>

#include <EEPROM.h>

#include <ErrorManager.h>

extern ErrorManager errormanager;

WiFiClient espClient;
PubSubClient client(espClient);

/***********************************************/
/*  C A L L B A C K                            */
/***********************************************/

/***********************************************/
void callback(char* topic, byte* payload, unsigned int length) {
/***********************************************/
  
  String Value="";
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  Serial.flush();
  int TypeCompensation = 0;
  if ((char)payload[0] == '#') {
      Serial.println("Compensation absolue"); 
      TypeCompensation =1;
  }
  else if ((char)payload[0] == '%') {
      Serial.println("Compensation par difference"); 
      TypeCompensation =2;    
  }
  else {
      Serial.println("Compensation relative");  
      TypeCompensation =0;   
  }
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    if (((char)payload[i] >= '0' && (char)payload[i] <= '9') || ((char)payload[i] == '.') || ((char)payload[i] == '-')) {
      Value = String(Value + (char)payload[i]);
    }
  }
  Serial.println();
  Serial.println("Valeur : " + Value);
  Serial.flush();

 String TmpTopic = String(topic);
 Serial.println("topic : " + TmpTopic);
 int bodyTag = TmpTopic.indexOf("comptemp");
/* Serial.print("bodytag : " );
 Serial.println(bodyTag);
 Serial.println(temperature);
 Serial.flush();*/

  if (bodyTag != -1) 
    {
      
      if (Value.toFloat() != 0) {
        if (TypeCompensation == 1)        
          data.CompensationTemp = Value.toFloat();
        else if (TypeCompensation == 2)
          data.CompensationTemp = Value.toFloat() - (data.temperature-data.CompensationTemp);
        else
          data.CompensationTemp = data.CompensationTemp + Value.toFloat();
      }
      else {
        data.CompensationTemp = 0;
      }

      EEPROM.begin(300);  //EEPROM.begin(Size)
      int EEaddress = 0;
/*      int integer_variable = 0;
  
      integer_variable = 12345;
//    EEaddress += EEPROM.put(EEaddress, integer_variable);
      EEaddress = data.EEPROMAnythingWrite(1, reinterpret_cast<char*>(&integer_variable), sizeof(integer_variable));*/

			int integer_variable = 12345;
      Serial.print("Tag Eeprom : ");
      Serial.println(integer_variable);
			EEPROM.put(EEaddress, integer_variable);
			EEaddress = EEaddress + sizeof(integer_variable);

			float floatingpoint_variable = 123.45;
			EEPROM.put(EEaddress, floatingpoint_variable);
			EEaddress = EEaddress + sizeof(floatingpoint_variable);

      floatingpoint_variable = data.CompensationTemp;
      EEaddress = EEaddress + sizeof(float) + (sizeof(float) * 0) + (sizeof(int) * 0);
      Serial.print("Adresse Eeprom : ");
      Serial.println(EEaddress);
//     EEaddress += EEPROM.put(EEaddress, floatingpoint_variable);
//      EEaddress = data.EEPROMAnythingWrite(EEaddress, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));
			EEPROM.put(EEaddress, floatingpoint_variable);
      EEPROM.commit();
      Serial.print("Sauvegarde compensation temp : ");
      Serial.println(data.CompensationTemp);

      EEPROM.end();
      exit;
    }

#ifdef DATATEMP2
 bodyTag = TmpTopic.indexOf("comptemp2");
/* Serial.print("bodytag : " );
 Serial.println(bodyTag);
 Serial.println(temperature);
 Serial.flush();*/

  if (bodyTag != -1) 
    {
      
      if (Value.toFloat() != 0) {
        if (TypeCompensation == 1)        
          data.CompensationTemp2 = Value.toFloat();
        else if (TypeCompensation == 2)
          data.CompensationTemp2 = Value.toFloat() - (data.temperature2-data.CompensationTemp2);
        else
          data.CompensationTemp2 = data.CompensationTemp2 + Value.toFloat();
      }
      else {
        data.CompensationTemp2 = 0;
      }

      EEPROM.begin(300);  //EEPROM.begin(Size)
      int EEaddress = 0;
//      int integer_variable = 0;
  
 /*     integer_variable = 12345;
//    EEaddress += EEPROM.put(EEaddress, integer_variable);
      EEaddress = data.EEPROMAnythingWrite(1, reinterpret_cast<char*>(&integer_variable), sizeof(integer_variable));

      float floatingpoint_variable = data.CompensationTemp2;
      EEaddress = EEaddress + (sizeof(floatingpoint_variable) * 2);
//     EEaddress += EEPROM.put(EEaddress, floatingpoint_variable);
      EEaddress = data.EEPROMAnythingWrite(EEaddress, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));*/

			int integer_variable = 12345;
      Serial.print("Tag Eeprom : ");
      Serial.println(integer_variable);
			EEPROM.put(EEaddress, integer_variable);
			
      float floatingpoint_variable = data.CompensationTemp2;
      EEaddress = EEaddress + sizeof(int) + sizeof(float) + (sizeof(float) * 1) + (sizeof(int) * 0);
      Serial.print("Adresse Eeprom : ");
      Serial.println(EEaddress);
			EEPROM.put(EEaddress, floatingpoint_variable);
			
      EEPROM.commit();
      Serial.print("Sauvegarde compensation temp2 : ");
      Serial.println(data.CompensationTemp2);

      EEPROM.end();
      exit;
    }
  #endif

 #ifdef DATATEMP3
  bodyTag = TmpTopic.indexOf("comptemp3");
/* Serial.print("bodytag : " );
 Serial.println(bodyTag);
 Serial.println(temperature);
 Serial.flush();*/

  if (bodyTag != -1) 
    {
      
      if (Value.toFloat() != 0) {
        if (TypeCompensation == 1)        
          data.CompensationTemp3 = Value.toFloat();
        else if (TypeCompensation == 2)
          data.CompensationTemp3 = Value.toFloat() - (data.temperature3-data.CompensationTemp3);
        else
          data.CompensationTemp3 = data.CompensationTemp3 + Value.toFloat();
      }
      else {
        data.CompensationTemp3 = 0;
      }

      EEPROM.begin(300);  //EEPROM.begin(Size)
      int EEaddress = 0;
 /*     int integer_variable = 0;
  
      integer_variable = 12345;
//    EEaddress += EEPROM.put(EEaddress, integer_variable);
      EEaddress = data.EEPROMAnythingWrite(1, reinterpret_cast<char*>(&integer_variable), sizeof(integer_variable));

      float floatingpoint_variable = data.CompensationTemp3;
      EEaddress = EEaddress + (sizeof(floatingpoint_variable) * 3);
//     EEaddress += EEPROM.put(EEaddress, floatingpoint_variable);
      EEaddress = data.EEPROMAnythingWrite(EEaddress, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));*/

			int integer_variable = 12345;
      Serial.print("Tag Eeprom : ");
      Serial.println(integer_variable);
			EEPROM.put(EEaddress, integer_variable);
			
      float floatingpoint_variable = data.CompensationTemp3;
      EEaddress = EEaddress + sizeof(int) + sizeof(float) + (sizeof(float) * 2) + (sizeof(int) * 0);
      Serial.print("Adresse Eeprom : ");
      Serial.println(EEaddress);
			EEPROM.put(EEaddress, floatingpoint_variable);
 			
      EEPROM.commit();
      Serial.print("Sauvegarde compensation temp3 : ");
      Serial.println(data.CompensationTemp3);

      EEPROM.end();
      exit;
    }
  #endif

  bodyTag = TmpTopic.indexOf("comphumidity");
  if (bodyTag != -1) 
    {
       if (Value.toFloat() != 0) {
        if (TypeCompensation == 1)        
          data.CompensationHumidity = Value.toFloat();
        else if (TypeCompensation == 2)
          data.CompensationHumidity = Value.toFloat() - (data.humidity-data.CompensationHumidity);
        else
          data.CompensationHumidity = data.CompensationHumidity + Value.toFloat();
      }
      else {
        data.CompensationHumidity = 0;
      }

      EEPROM.begin(300);  //EEPROM.begin(Size)
      int EEaddress = 0;
/*      int integer_variable = 0;
  
      integer_variable = 12345;
//    EEaddress += EEPROM.put(EEaddress, integer_variable);
      EEaddress = data.EEPROMAnythingWrite(1, reinterpret_cast<char*>(&integer_variable), sizeof(integer_variable));

      float floatingpoint_variable = data.CompensationHumidity;
      EEaddress = EEaddress + (sizeof(floatingpoint_variable) * 4);
//     EEaddress += EEPROM.put(EEaddress, floatingpoint_variable);
      EEaddress = data.EEPROMAnythingWrite(EEaddress, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));*/

			int integer_variable = 12345;
      Serial.print("Tag Eeprom : ");
      Serial.println(integer_variable);
			EEPROM.put(EEaddress, integer_variable);
			
      float floatingpoint_variable = data.CompensationHumidity;
      EEaddress = EEaddress + sizeof(int) + sizeof(float) + (sizeof(float) * 3) + (sizeof(int) * 0);
      Serial.print("Adresse Eeprom : ");
      Serial.println(EEaddress);
			EEPROM.put(EEaddress, floatingpoint_variable);
			
      EEPROM.commit();
      EEPROM.end();
      exit;
    }

#ifdef DATAHUMIDITY2
  bodyTag = TmpTopic.indexOf("comphumidity2");
  if (bodyTag != -1) 
    {
       if (Value.toFloat() != 0) {
        if (TypeCompensation == 1)        
          data.CompensationHumidity2 = Value.toFloat();
        else if (TypeCompensation == 2)
          data.CompensationHumidity2 = Value.toFloat() - (data.humidity2-data.CompensationHumidity2);
        else
          data.CompensationHumidity2 = data.CompensationHumidity2 + Value.toFloat();
      }
      else {
        data.CompensationHumidity2 = 0;
      }

      EEPROM.begin(300);  //EEPROM.begin(Size)
      int EEaddress = 0;
/*      int integer_variable = 0;
  
      integer_variable = 12345;
//    EEaddress += EEPROM.put(EEaddress, integer_variable);
      EEaddress = data.EEPROMAnythingWrite(1, reinterpret_cast<char*>(&integer_variable), sizeof(integer_variable));

      float floatingpoint_variable = data.CompensationHumidity2;
      EEaddress = EEaddress + (sizeof(floatingpoint_variable) * 5);
//     EEaddress += EEPROM.put(EEaddress, floatingpoint_variable);
      EEaddress = data.EEPROMAnythingWrite(EEaddress, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));*/

			int integer_variable = 12345;
      Serial.print("Tag Eeprom : ");
      Serial.println(integer_variable);
			EEPROM.put(EEaddress, integer_variable);
			
      float floatingpoint_variable = data.CompensationHumidity2;
      EEaddress = EEaddress + sizeof(int) + sizeof(float) + (sizeof(float) * 4) + (sizeof(int) * 0);
      Serial.print("Adresse Eeprom : ");
      Serial.println(EEaddress);
			EEPROM.put(EEaddress, floatingpoint_variable);
			
      EEPROM.commit();
      EEPROM.end();
      exit;
    }
 #endif

#ifdef DATAHUMIDITY3
  bodyTag = TmpTopic.indexOf("comphumidity3");
  if (bodyTag != -1) 
    {
       if (Value.toFloat() != 0) {
        if (TypeCompensation == 1)        
          data.CompensationHumidity3 = Value.toFloat();
        else if (TypeCompensation == 2)
          data.CompensationHumidity3 = Value.toFloat() - (data.humidity3-data.CompensationHumidity3);
        else
          data.CompensationHumidity3 = data.CompensationHumidity3 + Value.toFloat();
      }
      else {
        data.CompensationHumidity3 = 0;
      }

      EEPROM.begin(300);  //EEPROM.begin(Size)
      int EEaddress = 0;
/*      int integer_variable = 0;
  
      integer_variable = 12345;
//    EEaddress += EEPROM.put(EEaddress, integer_variable);
      EEaddress = data.EEPROMAnythingWrite(1, reinterpret_cast<char*>(&integer_variable), sizeof(integer_variable));

      float floatingpoint_variable = data.CompensationHumidity3;
      EEaddress = EEaddress + (sizeof(floatingpoint_variable) * 6);
//     EEaddress += EEPROM.put(EEaddress, floatingpoint_variable);
      EEaddress = data.EEPROMAnythingWrite(EEaddress, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));*/

			int integer_variable = 12345;
      Serial.print("Tag Eeprom : ");
      Serial.println(integer_variable);
			EEPROM.put(EEaddress, integer_variable);
			
      float floatingpoint_variable = data.CompensationHumidity3;
      EEaddress = EEaddress + sizeof(int) + sizeof(float) + (sizeof(float) * 5) + (sizeof(int) * 0);
      Serial.print("Adresse Eeprom : ");
      Serial.println(EEaddress);
			EEPROM.put(EEaddress, floatingpoint_variable);
			
      EEPROM.commit();
      EEPROM.end();
      exit;
    }
 #endif

 
   bodyTag = TmpTopic.indexOf("complight");
   if (bodyTag != -1) 
     {
        if (Value.toFloat() != 0) {
        if (TypeCompensation == 1)        
          data.CompensationLight = Value.toFloat();
        else if (TypeCompensation == 2)
          data.CompensationLight = Value.toFloat() - (data.lux-data.CompensationLight);
        else
          data.CompensationLight = data.CompensationLight + Value.toFloat();
      }
      else {
        data.CompensationLight = 0;
      }


      EEPROM.begin(300);  //EEPROM.begin(Size)
      int EEaddress = 0;
/*      int integer_variable = 0;
  
      integer_variable = 12345;
//    EEaddress += EEPROM.put(EEaddress, integer_variable);
      EEaddress = data.EEPROMAnythingWrite(1, reinterpret_cast<char*>(&integer_variable), sizeof(integer_variable));

      float floatingpoint_variable = data.CompensationLight;
      EEaddress = EEaddress + (sizeof(floatingpoint_variable) * 7);
//     EEaddress += EEPROM.put(EEaddress, floatingpoint_variable);
      EEaddress = data.EEPROMAnythingWrite(EEaddress, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));*/

			int integer_variable = 12345;
      Serial.print("Tag Eeprom : ");
      Serial.println(integer_variable);
			EEPROM.put(EEaddress, integer_variable);
			
      float floatingpoint_variable = data.CompensationLight;
      EEaddress = EEaddress + sizeof(int) + sizeof(float) + (sizeof(float) * 6) + (sizeof(int) * 0);
      Serial.print("Adresse Eeprom : ");
      Serial.println(EEaddress);
			EEPROM.put(EEaddress, floatingpoint_variable);
			
      EEPROM.commit();
      EEPROM.end();
      exit;
    }  

#ifdef DATALIGHT2
   bodyTag = TmpTopic.indexOf("complight2");
   if (bodyTag != -1) 
     {
        if (Value.toFloat() != 0) {
        if (TypeCompensation == 1)        
          data.CompensationLight2 = Value.toFloat();
        else if (TypeCompensation == 2)
          data.CompensationLight2 = Value.toFloat() - (data.lux2-data.CompensationLight2);
        else
          data.CompensationLight2 = data.CompensationLight2 + Value.toFloat();
      }
      else {
        data.CompensationLight2 = 0;
      }


      EEPROM.begin(300);  //EEPROM.begin(Size)
      int EEaddress = 0;
/*      int integer_variable = 0;
  
      integer_variable = 12345;
//    EEaddress += EEPROM.put(EEaddress, integer_variable);
      EEaddress = data.EEPROMAnythingWrite(1, reinterpret_cast<char*>(&integer_variable), sizeof(integer_variable));

      float floatingpoint_variable = data.CompensationLight2;
      EEaddress = EEaddress + (sizeof(floatingpoint_variable) * 8);
//     EEaddress += EEPROM.put(EEaddress, floatingpoint_variable);
      EEaddress = data.EEPROMAnythingWrite(EEaddress, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));*/

			int integer_variable = 12345;
      Serial.print("Tag Eeprom : ");
      Serial.println(integer_variable);
			EEPROM.put(EEaddress, integer_variable);
			
      float floatingpoint_variable = data.CompensationLight2;
      EEaddress = EEaddress + sizeof(int) + sizeof(float) + (sizeof(float) * 7) + (sizeof(int) * 0);
      Serial.print("Adresse Eeprom : ");
      Serial.println(EEaddress);
			EEPROM.put(EEaddress, floatingpoint_variable);
			
      EEPROM.commit();
      EEPROM.end();
      exit;
    } 
 #endif

#ifdef DATALIGHT3
   bodyTag = TmpTopic.indexOf("complight3");
   if (bodyTag != -1) 
     {
        if (Value.toFloat() != 0) {
        if (TypeCompensation == 1)        
          data.CompensationLight3 = Value.toFloat();
        else if (TypeCompensation == 2)
          data.CompensationLight3 = Value.toFloat() - (data.lux3-data.CompensationLight3);
        else
          data.CompensationLight3 = data.CompensationLight3 + Value.toFloat();
      }
      else {
        data.CompensationLight3 = 0;
      }


      EEPROM.begin(300);  //EEPROM.begin(Size)
      int EEaddress = 0;
/*      int integer_variable = 0;
  
      integer_variable = 12345;
//    EEaddress += EEPROM.put(EEaddress, integer_variable);
      EEaddress = data.EEPROMAnythingWrite(1, reinterpret_cast<char*>(&integer_variable), sizeof(integer_variable));

      float floatingpoint_variable = data.CompensationLight3;
      EEaddress = EEaddress + (sizeof(floatingpoint_variable) * 9);
//     EEaddress += EEPROM.put(EEaddress, floatingpoint_variable);
      EEaddress = data.EEPROMAnythingWrite(EEaddress, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));*/

			int integer_variable = 12345;
      Serial.print("Tag Eeprom : ");
      Serial.println(integer_variable);
			EEPROM.put(EEaddress, integer_variable);
			
      float floatingpoint_variable = data.CompensationLight3;
      EEaddress = EEaddress + sizeof(int) + sizeof(float) + (sizeof(float) * 8) + (sizeof(int) * 0);
      Serial.print("Adresse Eeprom : ");
      Serial.println(EEaddress);
			EEPROM.put(EEaddress, floatingpoint_variable);
			
      EEPROM.commit();
      EEPROM.end();
      exit;
    } 
 #endif
 
   bodyTag = TmpTopic.indexOf("comppressure");
   if (bodyTag != -1) 
     {
       

        if (Value.toFloat() != 0) {
        if (TypeCompensation == 1)        
          data.CompensationPressure = Value.toFloat();
        else if (TypeCompensation == 2)
          data.CompensationPressure = Value.toFloat() - (data.pressure-data.CompensationPressure);
        else
          data.CompensationPressure = data.CompensationPressure + Value.toFloat();
      }
      else {
        data.CompensationPressure = 0;
      }

      EEPROM.begin(300);  //EEPROM.begin(Size)
      int EEaddress = 0;
/*      int integer_variable = 0;
  
      integer_variable = 12345;
//    EEaddress += EEPROM.put(EEaddress, integer_variable);
      EEaddress = data.EEPROMAnythingWrite(1, reinterpret_cast<char*>(&integer_variable), sizeof(integer_variable));

      float floatingpoint_variable = data.CompensationPressure;
      EEaddress = EEaddress + (sizeof(floatingpoint_variable) * 10);
//     EEaddress += EEPROM.put(EEaddress, floatingpoint_variable);
      EEaddress = data.EEPROMAnythingWrite(EEaddress, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));*/
			
			int integer_variable = 12345;
      Serial.print("Tag Eeprom : ");
      Serial.println(integer_variable);
			EEPROM.put(EEaddress, integer_variable);

      float floatingpoint_variable = data.CompensationPressure;
      EEaddress = EEaddress + sizeof(int) + sizeof(float) + (sizeof(float) * 9) + (sizeof(int) * 0);
      Serial.print("Adresse Eeprom : ");
      Serial.println(EEaddress);
			EEPROM.put(EEaddress, floatingpoint_variable);
			
      EEPROM.commit();
      EEPROM.end();
      exit;
    } 

#ifdef DATAPRESSURE2
   bodyTag = TmpTopic.indexOf("comppressure2");
   if (bodyTag != -1) 
     {
       

        if (Value.toFloat() != 0) {
        if (TypeCompensation == 1)        
          data.CompensationPressure2 = Value.toFloat();
        else if (TypeCompensation == 2)
          data.CompensationPressure2 = Value.toFloat() - (data.pressure2-data.CompensationPressure2);
        else
          data.CompensationPressure2 = data.CompensationPressure2 + Value.toFloat();
      }
      else {
        data.CompensationPressure2 = 0;
      }

      EEPROM.begin(300);  //EEPROM.begin(Size)
      int EEaddress = 0;
/*      int integer_variable = 0;
  
      integer_variable = 12345;
//    EEaddress += EEPROM.put(EEaddress, integer_variable);
      EEaddress = data.EEPROMAnythingWrite(1, reinterpret_cast<char*>(&integer_variable), sizeof(integer_variable));

      float floatingpoint_variable = data.CompensationPressure2;
      EEaddress = EEaddress + (sizeof(floatingpoint_variable) * 11);
//     EEaddress += EEPROM.put(EEaddress, floatingpoint_variable);
      EEaddress = data.EEPROMAnythingWrite(EEaddress, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));*/

			int integer_variable = 12345;
      Serial.print("Tag Eeprom : ");
      Serial.println(integer_variable);
			EEPROM.put(EEaddress, integer_variable);
			
      float floatingpoint_variable = data.CompensationPressure2;
      EEaddress = EEaddress + sizeof(int) + sizeof(float) + (sizeof(float) * 10) + (sizeof(int) * 0);
      Serial.print("Adresse Eeprom : ");
      Serial.println(EEaddress);
			EEPROM.put(EEaddress, floatingpoint_variable);
			
      EEPROM.commit();
      EEPROM.end();
      exit;
    } 
 #endif


#ifdef DATAPRESSURE3
   bodyTag = TmpTopic.indexOf("comppressure3");
   if (bodyTag != -1) 
     {
       

        if (Value.toFloat() != 0) {
        if (TypeCompensation == 1)        
          data.CompensationPressure3 = Value.toFloat();
        else if (TypeCompensation == 2)
          data.CompensationPressure3 = Value.toFloat() - (data.pressure3-data.CompensationPressure3);
        else
          data.CompensationPressure3 = data.CompensationPressure3 + Value.toFloat();
      }
      else {
        data.CompensationPressure3 = 0;
      }

      EEPROM.begin(300);  //EEPROM.begin(Size)
      int EEaddress = 0;
/*      int integer_variable = 0;
  
      integer_variable = 12345;
//    EEaddress += EEPROM.put(EEaddress, integer_variable);
      EEaddress = data.EEPROMAnythingWrite(1, reinterpret_cast<char*>(&integer_variable), sizeof(integer_variable));

      float floatingpoint_variable = data.CompensationPressure3;
      EEaddress = EEaddress + (sizeof(floatingpoint_variable) * 12);
//     EEaddress += EEPROM.put(EEaddress, floatingpoint_variable);
      EEaddress = data.EEPROMAnythingWrite(EEaddress, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));*/

			int integer_variable = 12345;
      Serial.print("Tag Eeprom : ");
      Serial.println(integer_variable);
			EEPROM.put(EEaddress, integer_variable);
			
      float floatingpoint_variable = data.CompensationPressure3;
      EEaddress = EEaddress + sizeof(int) + sizeof(float) + (sizeof(float) * 11) + (sizeof(int) * 0);
      Serial.print("Adresse Eeprom : ");
      Serial.println(EEaddress);
			EEPROM.put(EEaddress, floatingpoint_variable);
			
      EEPROM.commit();
      EEPROM.end();
      exit;
    } 
 #endif
 
   bodyTag = TmpTopic.indexOf("timezone");
   if (bodyTag != -1) 
     {
       
      webserver.timezone = Value.toInt();
      Serial.print("Timezone maj topic: ");
      Serial.println(webserver.timezone);
      Serial.flush();

      EEPROM.begin(300);  //EEPROM.begin(Size)
      int EEaddress = 0;
      int integer_variable = 0;
  
/*      integer_variable = 12345;
//    EEaddress += EEPROM.put(EEaddress, integer_variable);
      EEaddress = data.EEPROMAnythingWrite(1, reinterpret_cast<char*>(&integer_variable), sizeof(integer_variable));

      integer_variable = webserver.timezone;
      float floatingpoint_variable = webserver.timezone;
      EEaddress = EEaddress + (sizeof(floatingpoint_variable) * 13);
//    EEaddress += EEPROM.put(EEaddress, integer_variable);
      EEaddress = data.EEPROMAnythingWrite(EEaddress, reinterpret_cast<char*>(&integer_variable), sizeof(integer_variable));*/

			integer_variable = 12345;
      Serial.print("Tag Eeprom : ");
      Serial.println(integer_variable);
			EEPROM.put(EEaddress, integer_variable);

      integer_variable = webserver.timezone;
      EEaddress = EEaddress + sizeof(int) + sizeof(float) + (sizeof(float) * 12) + (sizeof(int) * 0);
      Serial.print("Adresse Eeprom : ");
      Serial.println(EEaddress);
			EEPROM.put(EEaddress, integer_variable);
           
      EEPROM.commit();
      EEPROM.end();


#ifndef DATALOGGER
      Serial.print("Timezone : ");
      Serial.println(webserver.timezone);
      Serial.print("SummerTime : ");
      Serial.println(webserver.summertime);

      configTime((webserver.timezone+webserver.summertime) * 3600, webserver.dst * 0, "pool.ntp.org", "time.nist.gov");
      Serial.println("\nWaiting for time");
      int compteurtime = 0;
      while ((!time(nullptr)) && (compteurtime++ < 100)) {
        Serial.print(".");
        delay(1000);
      }
#endif

      NTP.stop();
      // Démarrage du processus NTP
      NTP.begin (ntpServer, webserver.timezone, webserver.dayligthSaving, webserver.minutesOffset);
      // Interval de synchronisation en seconde (30 min.)
      NTP.setInterval (1800);
            
      exit;
    } 

   bodyTag = TmpTopic.indexOf("summertime");
   if (bodyTag != -1) 
     {
       
      webserver.summertime = Value.toInt();
      if ((webserver.summertime != 0) && (webserver.summertime != 1)) webserver.summertime = 0;
      Serial.print("SummerTime maj topic: ");
      Serial.println(webserver.summertime);
      Serial.flush();

      EEPROM.begin(300);  //EEPROM.begin(Size)
      int EEaddress = 0;
      int integer_variable = 0;
  
/*      integer_variable = 12345;
//    EEaddress += EEPROM.put(EEaddress, integer_variable);
      EEaddress = data.EEPROMAnythingWrite(1, reinterpret_cast<char*>(&integer_variable), sizeof(integer_variable));

      integer_variable = webserver.summertime;
      float floatingpoint_variable = webserver.summertime;
      EEaddress = EEaddress + (sizeof(floatingpoint_variable) * 13)+sizeof(integer_variable);
//    EEaddress += EEPROM.put(EEaddress, integer_variable);
      EEaddress = data.EEPROMAnythingWrite(EEaddress, reinterpret_cast<char*>(&integer_variable), sizeof(integer_variable));*/

			integer_variable = 12345;
      Serial.print("Tag Eeprom : ");
      Serial.println(integer_variable);
			EEPROM.put(EEaddress, integer_variable);
			
      integer_variable = webserver.summertime;
      EEaddress = EEaddress + sizeof(int) + sizeof(float) + (sizeof(float) * 12) + (sizeof(int) * 1);
      Serial.print("Adresse Eeprom : ");
      Serial.println(EEaddress);
			EEPROM.put(EEaddress, integer_variable);
			
           
      EEPROM.commit();
      EEPROM.end();


#ifndef DATALOGGER
      Serial.print("Timezone : ");
      Serial.println(webserver.timezone);
      Serial.print("SummerTime : ");
      Serial.println(webserver.summertime);

      configTime((webserver.timezone+webserver.summertime) * 3600, webserver.dst * 0, "pool.ntp.org", "time.nist.gov");
      Serial.println("\nWaiting for time");
      int compteurtime = 0;
      while ((!time(nullptr)) && (compteurtime++ < 100)) {
        Serial.print(".");
        delay(1000);
      }
#endif
           
      exit;
    }          
    
  bodyTag = TmpTopic.indexOf("led");
  if (bodyTag != -1) 
    {
  
     // Switch on the LED if an 1 was received as first character
     if ((char)payload[0] == '0') {      
        digitalWrite(LED_BUILTIN, LOW);   // Turn the LED off 
     } else {
       digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED on by making the voltage HIGH
     }
   }

  bodyTag = TmpTopic.indexOf("mqtt");
  if (bodyTag != -1) 
    {
  
     // Switch on the MQTT if an 1 was received as first character
     if ((char)payload[0] == '0') {      
       // Turn mqtt off
       webserver.mqtt_enable = false; 
     } else {
       // Turn mqtt on
       webserver.mqtt_enable = true;
     }
   }

  bodyTag = TmpTopic.indexOf("reboot");
  if (bodyTag != -1) 
    {     
    Serial.println("Reboot..");
    ESP.restart();    
    }   

  bodyTag = TmpTopic.indexOf("numsonde");
  if (bodyTag != -1) 
    {
      if (Value.toInt() != 0) {
         data.sondeNumber = Value.toInt();
         Serial.print("Sonde n° : ");
         Serial.println(data.sondeNumber);
      }

      EEPROM.begin(300);  //EEPROM.begin(Size)
      int EEaddress = 0;
      int integer_variable = 0;
  
/*      integer_variable = 12345;
//    EEaddress += EEPROM.put(EEaddress, integer_variable);
      EEaddress = data.EEPROMAnythingWrite(1, reinterpret_cast<char*>(&integer_variable), sizeof(integer_variable));

      integer_variable = data.sondeNumber;
      EEaddress = EEaddress + (sizeof(float) * 13)+ (sizeof(integer_variable) * 3);
//     EEaddress += EEPROM.put(EEaddress, floatingpoint_variable);
      EEaddress = data.EEPROMAnythingWrite(EEaddress, reinterpret_cast<char*>(&integer_variable), sizeof(integer_variable));*/

			integer_variable = 12345;
      Serial.print("Tag Eeprom : ");
      Serial.println(integer_variable);
			EEPROM.put(EEaddress, integer_variable);
			
      integer_variable = data.sondeNumber;
      EEaddress = EEaddress + sizeof(int) + sizeof(float) + (sizeof(float) * 12) + (sizeof(int) * 3);
      Serial.print("Adresse Eeprom : ");
      Serial.println(EEaddress);
			EEPROM.put(EEaddress, integer_variable);
			
      EEPROM.commit();
      EEPROM.end();
      exit;
    }
 
  bodyTag = TmpTopic.indexOf("mqttaddress");
  if (bodyTag != -1) 
    {
			if (Value != "") {
         Value.toCharArray(webserver.mqtt_server4,16);
         Serial.print("Adresse serveur Mqtt : ");
         Serial.println(webserver.mqtt_server4);
      }

      EEPROM.begin(300);  //EEPROM.begin(Size)
      int EEaddress = 0;
/*      int integer_variable = 0;
  
      integer_variable = 12345;
//    EEaddress += EEPROM.put(EEaddress, integer_variable);
      EEaddress = data.EEPROMAnythingWrite(1, reinterpret_cast<char*>(&integer_variable), sizeof(integer_variable));

      EEaddress = EEaddress + (sizeof(float) * 13)+ (sizeof(integer_variable) * 4);
//     EEaddress += EEPROM.put(EEaddress, floatingpoint_variable);
      EEaddress = data.EEPROMAnythingWrite(EEaddress, reinterpret_cast<char*>(&webserver.mqtt_server4), sizeof(webserver.mqtt_server4));*/

			int integer_variable = 12345;
      Serial.print("Tag Eeprom : ");
      Serial.println(integer_variable);
			EEPROM.put(EEaddress, integer_variable);
			
      EEaddress = EEaddress + sizeof(int) + sizeof(float) + (sizeof(float) * 12) + (sizeof(int) * 4);
      Serial.print("Adresse Eeprom : ");
      Serial.println(EEaddress);
			EEPROM.put(EEaddress, webserver.mqtt_server4);
			
      EEPROM.commit();
      EEPROM.end();
      exit;
    }
 
  bodyTag = TmpTopic.indexOf("erasemqttadr");
  if (bodyTag != -1) 
    {
      Serial.println("Reset Adresse serveur Mqtt");

			strcpy(webserver.mqtt_server4, "");
      EEPROM.begin(300);  //EEPROM.begin(Size)
      int EEaddress = 0;
/*      int integer_variable = 0;
  
      integer_variable = 12345;
//    EEaddress += EEPROM.put(EEaddress, integer_variable);
      EEaddress = data.EEPROMAnythingWrite(1, reinterpret_cast<char*>(&integer_variable), sizeof(integer_variable));

      EEaddress = EEaddress + (sizeof(float) * 13)+ (sizeof(integer_variable) * 4);
//     EEaddress += EEPROM.put(EEaddress, floatingpoint_variable);
      EEaddress = data.EEPROMAnythingWrite(EEaddress, reinterpret_cast<char*>(&webserver.mqtt_server4), sizeof(webserver.mqtt_server4));*/

			int integer_variable = 12345;
      Serial.print("Tag Eeprom : ");
      Serial.println(integer_variable);
			EEPROM.put(EEaddress, integer_variable);
			
      EEaddress = EEaddress + sizeof(int) + sizeof(float) + (sizeof(float) * 12) + (sizeof(int) * 4);
      Serial.print("Adresse Eeprom : ");
      Serial.println(EEaddress);
			EEPROM.put(EEaddress, webserver.mqtt_server4);
			
      EEPROM.commit();
      EEPROM.end();
      exit;
    }
 
}

/********************************************/
/* R E C O N N E C T                        */
/********************************************/

/********************************************/
void WebServer::reconnect(void) {
/********************************************/
  // Loop until we're reconnected
  compteur = 0;
	
	char msgTopic[50];

  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ENSACF-ESP8266Cli-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect

 #ifdef MQTT_USER && MQTT_PASSWORD
    Serial.println("connection MQTT avec Authentification");
    if (client.connect(clientId.c_str(),MQTT_USER,MQTT_PASSWORD)) {
 #else   
    Serial.println("connection MQTT sans Authentification");
    if (client.connect(clientId.c_str())) {
 #endif     
    
      Serial.println("connected");
      
       strcpy(msgTopic,TOPIC);
       strcat(msgTopic,data.CapteurID);
       strcat(msgTopic,"connection status");

      // Once connected, publish an announcement...
      client.publish(msgTopic, "hello world");
      // ... and resubscribe

       strcpy(msgTopic,TOPIC);
       strcat(msgTopic,data.CapteurID);
       strcat(msgTopic,COMPTEMP_TOPIC);     
       client.subscribe(msgTopic);

#ifdef DATATEMP2
       strcpy(msgTopic,TOPIC);
       strcat(msgTopic,data.CapteurID);
       strcat(msgTopic,COMPTEMP2_TOPIC);     
       client.subscribe(msgTopic);
#endif

#ifdef DATATEMP2
       strcpy(msgTopic,TOPIC);
       strcat(msgTopic,data.CapteurID);
       strcat(msgTopic,COMPTEMP3_TOPIC);     
       client.subscribe(msgTopic);
#endif

       strcpy(msgTopic,TOPIC);
       strcat(msgTopic,data.CapteurID);
       strcat(msgTopic,COMPHUMIDITY_TOPIC);     
       client.subscribe(msgTopic);

#ifdef DATAHUMIDITY2
       strcpy(msgTopic,TOPIC);
       strcat(msgTopic,data.CapteurID);
       strcat(msgTopic,COMPHUMIDITY2_TOPIC);     
       client.subscribe(msgTopic);
#endif

#ifdef DATAHUMIDITY3
       strcpy(msgTopic,TOPIC);
       strcat(msgTopic,data.CapteurID);
       strcat(msgTopic,COMPHUMIDITY3_TOPIC);     
       client.subscribe(msgTopic);
#endif

       strcpy(msgTopic,TOPIC);
       strcat(msgTopic,data.CapteurID);
       strcat(msgTopic,COMPLIGHT_TOPIC);     
       client.subscribe(msgTopic);

#ifdef DATALIGHT2
       strcpy(msgTopic,TOPIC);
       strcat(msgTopic,data.CapteurID);
       strcat(msgTopic,COMPLIGHT2_TOPIC);     
       client.subscribe(msgTopic);
#endif

#ifdef DATALIGHT3
       strcpy(msgTopic,TOPIC);
       strcat(msgTopic,data.CapteurID);
       strcat(msgTopic,COMPLIGHT3_TOPIC);     
       client.subscribe(msgTopic);
#endif

       strcpy(msgTopic,TOPIC);
       strcat(msgTopic,data.CapteurID);
       strcat(msgTopic,COMPPRESURE_TOPIC);     
       client.subscribe(msgTopic);

#ifdef DATAPRESSURE2
       strcpy(msgTopic,TOPIC);
       strcat(msgTopic,data.CapteurID);
       strcat(msgTopic,COMPPRESURE2_TOPIC);     
       client.subscribe(msgTopic);
#endif

#ifdef DATAPRESSURE3
       strcpy(msgTopic,TOPIC);
       strcat(msgTopic,data.CapteurID);
       strcat(msgTopic,COMPPRESURE3_TOPIC);     
       client.subscribe(msgTopic);
#endif
       strcpy(msgTopic,TOPIC);
       strcat(msgTopic,data.CapteurID);
       strcat(msgTopic,TIMEZONE_TOPIC);     
       client.subscribe(msgTopic);

       strcpy(msgTopic,TOPIC);
       strcat(msgTopic,data.CapteurID);
       strcat(msgTopic,SUMMERTIME_TOPIC);     
       client.subscribe(msgTopic);

       strcpy(msgTopic,TOPIC);
       strcat(msgTopic,data.CapteurID);
       strcat(msgTopic,MQTT_TOPIC);     
       client.subscribe(msgTopic);

       strcpy(msgTopic,TOPIC);
       strcat(msgTopic,data.CapteurID);
       strcat(msgTopic,REBOOT_TOPIC);     
       client.subscribe(msgTopic);

       strcpy(msgTopic,TOPIC);
       strcat(msgTopic,data.CapteurID);
       strcat(msgTopic,NUMSONDE_TOPIC);     
       client.subscribe(msgTopic);

       strcpy(msgTopic,TOPIC);
       strcat(msgTopic,data.CapteurID);
       strcat(msgTopic,MQTTADDRESS_TOPIC);     
       client.subscribe(msgTopic);

       strcpy(msgTopic,TOPIC);
       strcat(msgTopic,data.CapteurID);
       strcat(msgTopic,RESETMQTTADDRESS_TOPIC);     
       client.subscribe(msgTopic);
              
       Status[2] = 'M';
       mqttconnected = true;   
       errormanager.SetMqttActif();

    } else {
      if (compteur > 10) {     
        errormanager.SetErrorMqtt();
        exit;
      }
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
      compteur++;
    }
  }

/*  // Démarrage du processus NTP
  NTP.begin (ntpServer, timezone, dayligthSaving, minutesOffset);
  // Interval de synchronisation en seconde (30 min.)
  NTP.setInterval (1800);*/

}

/****************************************************/
/*       ProcessNtpEvent                            */
/****************************************************/

/****************************************************/
void WebServer::processNtpEvent (NTPSyncEvent_t ntpEvent) {
/****************************************************/
  if (ntpEvent) {
    Serial.print ("Erreur de synchronisation: ");
    ErrorEventNTP = true;
    if (ntpEvent == noResponse)
      Serial.println ("Serveur NTP injoignable");
    else if (ntpEvent == invalidAddress)
      Serial.println ("Adresse du serveur NTP invalide");
  } else {
    Serial.print ("Récupération du temps NTP: ");
    Serial.println (NTP.getTimeDateString (NTP.getLastNTPSync ()));
    ErrorEventNTP = false;
  }
}

/********************************************/
void WebServer::init(void) {
/********************************************/
  Status[0] = '-';
  Status[1] = ' ';
  Status[2] = '_';
  Status[3] = ' ';
  Status[4] = '_';
  Status[5] = '\0';
}

/********************************************/
/*   S E T U P _ W I F I                    */
/********************************************/

/********************************************/
boolean WebServer::setup_wifi() {
/********************************************/

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
//  Serial.print("Connecting to ");
//  Serial.println(ssid);

 // WiFi.disconnect(); 

#ifdef IP_FIXE
  Serial.print("ip : ");
  Serial.print(ip);
  Serial.print(" Dns : ");
  Serial.print(dns);
  Serial.print(" Gayteway : ");
  Serial.print(gateway);
  Serial.print(" subnet : ");
  Serial.print(subnet);

  WiFi.config(ip, dns, gateway, subnet);
//  //WiFi.mode(WIFI_STA);
#endif

  WiFi.mode(WIFI_STA);

  wifiMulti.addAP(ssid1, password1);
  wifiMulti.addAP(ssid2, password2);
  wifiMulti.addAP(ssid3, password3);

  Serial.println("Connecting Wifi...");

//  WiFi.begin(ssid, password);
  delay(2000);

/*  compteur = 0;
  WifiConnection = true;
  while (WiFi.status() != WL_CONNECTED) {
    if (compteur > 10) 
      {
        WifiConnection = false;
        break;
      }
    delay(500);
    Serial.print(".");
    compteur++;
  }
}*/
  

    // Wait for connection
  for (int i = 0; i < 25; i++)
  {
    if ( wifiMulti.run() != WL_CONNECTED ) {
      //WiFi.status() != WL_CONNECTED ) {
      WifiConnection = false;
      delay ( 250 );
      Serial.print ( "." );
      delay ( 250 );
    }
    else {
       WifiConnection = true; 
       errormanager.SetWifiActif();
    }  
  }
  
  randomSeed(micros());
 
  if (WifiConnection == true)
    {
      Serial.println("");
      Serial.println("WiFi connected");
      Serial.print("SSID: ");
      Serial.println(WiFi.SSID());
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
      Serial.print("Gateway : ");
      Serial.println(WiFi.gatewayIP().toString().c_str());
      Serial.print("Host name : ");
      Serial.println(WiFi.hostname());
      sprintf(adresseip, "%d.%d.%d.%d", WiFi.localIP()[0], WiFi.localIP()[1], WiFi.localIP()[2], WiFi.localIP()[3] );

#ifdef DATALOGGER
      Serial.print("Timezone - wifi_config : ");
      Serial.println(timezone);
      Serial.print("SummerTime - wifi_config : ");
      Serial.println(summertime);

      configTime((timezone+summertime) * 3600, dst * 0, "pool.ntp.org", "time.nist.gov");
      Serial.println("\nWaiting for time");
      int compteurtime = 0;
      while ((!time(nullptr)) && (compteurtime++ < 10)) {
        Serial.print(".");
        delay(1000);
      }
      println("");
#endif

    // Démarrage du processus NTP
    int tmpcompteur = 0;
    Serial.print("connection NTP  ");
    while ((!NTP.begin (ntpServer, timezone, dayligthSaving, minutesOffset)) && (tmpcompteur++ < 15)) {     
      Serial.print(".");
      delay(1000);
    }
    Serial.println("");

    if (tmpcompteur >= 15) errormanager.SetErrorNTP();
    
    // Interval de synchronisation en seconde (30 min.)
    NTP.setInterval (1800);

    //Mise en place mise a jour sans fil Wifi - OTA

    // Port defaults to 8266
    // ArduinoOTA.setPort(8266);
   
    // Hostname defaults to esp8266-[ChipID]
    ArduinoOTA.setHostname(data.CapteurName);
   
    // No authentication by default
    ArduinoOTA.setPassword((const char *)PASSWORD_WEB);
   
    ArduinoOTA.onStart([]() {
      Serial.println("Start");
    });
    
    ArduinoOTA.onEnd([]() {
      Serial.println("\nEnd");
    });
    
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    });
    
    ArduinoOTA.onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });
    
    ArduinoOTA.begin();
    Serial.println("Ready");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

     return true;
    }
  else
    {
      Serial.println("");
      Serial.println("WiFi not connected");      
      return false;
    }
}
