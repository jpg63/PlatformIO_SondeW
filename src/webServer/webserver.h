/* webserver -- 
 *
 * Copyright 2020 Jean-philippe GOI
 * 
 */

/*********************************************************************************/
/*                                                                               */
/*                           WebSite                                             */
/*                                                                               */
/*  version    Date        Description                                           */
/*    1.0      28/12/20                                                          */
/*    1.0.1    21/01/21    Modif gestion eeprom                                  */
/*                                                                               */
/*																																							 */
/*********************************************************************************/


#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <Arduino.h>

#include "settings.h"

#include <ESP8266WiFiMulti.h>
#include <NtpClientLib.h>

void callback(char* topic, byte* payload, unsigned int length);

 	// Serveur NTP
const char ntpServer[] = "pool.ntp.org";

class WebServer 
{

public:

  char Status[6];
	int timezone   = TIMEZONE;
	int summertime = SUMMERTIME;
		
	boolean ErrorEventNTP = false;

	bool WifiConnection = true;
	int compteurMqtt = 0;
	boolean wificonnected;
	boolean mqttconnected;
	boolean wifidesactived = false;

	boolean mqtt_enable = true;
	int compteurwifiinactif = 0;
	int compteurmqttinactif = 0;

	unsigned long oldtime;

/*     WIFI  et MQTT     */

/* change it with your ssid-password */
	const char* ssid1 = SSID1;
	const char* password1 = PASSWORD1;
/* this is the IP of PC/raspberry where you installed MQTT Server 
on Wins use "ipconfig" 
on Linux use "ifconfig" to get its IP address */
	const char* mqtt_server1 = MQTT_SERVER1;

	const char* ssid2 = SSID2;
	const char* password2 = PASSWORD2;
	const char* mqtt_server2 = MQTT_SERVER2;

	const char* ssid3 = SSID3;
	const char* password3 = PASSWORD3;
	const char* mqtt_server3 = MQTT_SERVER3;

	const char* ssid4 = "";
	const char* password4 = "";
	char mqtt_server4[17] = "";

	char adresseip[50];
	char timemesure[50];

	int dst = 0;
	int compteur = 0;

	// Le fuseau utilise les horaires été / hiver
	bool dayligthSaving = true;
	// Minutes d'offset à ajouter
	int8_t minutesOffset = 0;

	char  wifiSSID[50];
	char  wifiPwd[50];
	char  mqqtServeur[50];
	char  wifissidconf[20] = "";
	char  wifipwdconf[20]  = "";
	
	void init(void);
	boolean setup_wifi(void);
  void processNtpEvent (NTPSyncEvent_t ntpEvent);
	void reconnect(void);

};

extern ESP8266WiFiMulti wifiMulti;
extern WebServer webserver;


#endif
