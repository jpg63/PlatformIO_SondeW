#ifndef ERRORMANAGER_H
#define ERRORMANAGER_H

#include <Arduino.h>
#include <settings.h>
#include <PubSubClient.h>


/*----------------------------*/
/*        ERRORMANAGER        */
/*    Gestion des Erreurs     */
/*                            */
/*----------------------------*/

#define TIME_ERROR_CAPTEUR 60000 //300000  //5 min
#define TIME_ERROR_MQTT 600000  //10 min
#define TIME_ERROR_WIFI 1200000  //20 min

class ErrorManager {

 public:
   boolean Begin(void);
   void SetErrorWifi(void);
   void SetErrorMqtt(void);
   void SetErrorCapteur(void);
   void SetErrorNTP(void);
   void SetErrorSD(void);
   void Handle(void);
   void SetWifiActif(void);
   void SetMqttActif(void);

  private:
    int NbErrorWifi;
	int NbErrorMqtt;
	int NbErrorCapteur;
	int NbErrorNTP;
	int NbErrorSD;
	int NbReboot;
	unsigned long CompteurHandle = 0;
	
	bool   WifiActif = false;
	bool   MqttActif = false;
	bool   ResetCapteur = false;
	bool   ResetMqtt = false;
	bool   ResetWifi = false;

    unsigned long TimeWifi = 0;
    unsigned long TimeMqtt = 0;
    unsigned long TimeCapteur = 0;
    unsigned long TimeNTP = 0;
    unsigned long TimeSD = 0;
	
	void Reboot(void);
	void SaveEeprom(int nbreboot);
};

#endif

extern boolean mqtt_enable;
extern boolean wificonnected;
extern int nbreboot;

extern WiFiClient espClient;
extern PubSubClient client;

extern int EEPROMAnythingWrite(int pos, char *valeur, int longueur);
extern int EEPROMAnythingRead(int pos, char *zeichen, int lenge);
