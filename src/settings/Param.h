#ifndef PARAM_H_
#define PARAM_H_

// CAPTEUR 
#define CAPTEURID "21"         //Numero du capteur

//Peripherique
#define SCREEN
//#define DATALOGGER

//Capteurs

//Temperature
//#define SENSOR_SHT30               
//#define SENSOR_DS18B20             
//#define SENSOR_BMP180				 
//#define SENSOR_DHT11   // Grand rectangle bleu  
#define SENSOR_DHT12   // Petit rectangle bleu
//#define SENSOR_DHT21   // DHT 21 (AM2301) // grand rectangle noir   Pas teste
//#define SENSOR_DHT22   // DHT 22  (AM2302), AM2321 grand rectangle blanc

/*
DHT22
The DHT22/AM2302 sensor is able to measure temperatures from -40 to + 125 °c 
with an accuracy of +/-0.5 °c and relative humidity levels from 0 to 100% 
with an accuracy of +/-2% ( +/-5% at extremes, to 10% and 90% ).

A measurement can be performed every 500 milliseconds ( twice per second ).

DHT11
The DHT11 sensor is able to measure temperatures from 0 to + 50 °c 
with an accuracy of +/-2 °c and relative humidity levels of 20 to 80% 
with an accuracy of +/-5%. A measurement can be done every second.

Then, the DHT22 will be better to use.

But … in this project I will show you how to use DHT11 and DHT22.

However, the DHT11 has a lower cost.
*/


//Light
//#define SENSOR_BH1750

#ifdef SENSOR_BMP180
#define ALTITUDE 380.0 // Altitude de reference, correspondant à la pression mesurée
#endif

// RESET CONFIGURATION
//#define RESETCOMP  //Mise à jour de la memoire avec les compensations initiales

#define VERSIONPARAM 1.01

//Compensation 
// fixe la compensation du capteur (à la compilation)
#define COMPTEMP 0.00
#define COMPTEMP2 0.00
#define COMPTEMP3 0.00
#define COMPHUMIDITY 0.00
#define COMPHUMIDITY2 0.00
#define COMPHUMIDITY3 0.00
#define COMPLIGHT 0.00
#define COMPLIGHT2 0.00
#define COMPLIGHT3 0.00
#define COMPPRESSURE 0.00
#define COMPPRESSURE2 0.00
#define COMPPRESSURE3 0.00

//Mesures
#define NB_MESURE 5       //Nombre de mesure avant affichage OLED (moyenne)
#define COMPTEUR_MQTT 2   //Envoi tout les MQTT COMPTEUR_MQTT X NB_MESURE mesures

//environ 1 mesure toutes les 2 secondes - Ce temps peut être plus faible mais certain capteurs ne fonctionneront plus

// WIFI - MQTT Serveur
//#define SSID1  "Livebox-23D2"
//#define PASSWORD1 "F76C6CA7A22666D2742F7E1D4F"

#define SSID1  "Livebox-D2D0"
#define PASSWORD1 "SCXVY2JX5ztqopNAwU"
/* this is the IP of PC/raspberry where you installed MQTT Server 
on Wins use "ipconfig" 
on Linux use "ifconfig" to get its IP address */
//#define MQTT_SERVER1 "194.199.192.212"  //jeedom
//#define MQTT_SERVER1 "192.168.1.201"    //MQTT TEST
#define MQTT_SERVER1 "194.199.192.219"   //jeedom2

#define SSID2 "WIFI-MAINTENANCE"
#define PASSWORD2 "leti1999"
//#define MQTT_SERVER2 "192.168.1.200"   //jeedom
#define MQTT_SERVER2 "192.168.1.201"   //jeedom2

#define SSID3 "jeedom"
#define PASSWORD3 "jeedom"
#define MQTT_SERVER3 "194.199.192.219"

//#define IP_FIXE		//DHCP ou IP FIXE

#ifdef IP_FIXE
IPAddress ip(192, 168, 1, 30);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 0, 0);
IPAddress dns(8, 8, 8, 8);
#endif

// Login + password Mosquitto
#define MQTT_USER "jeedom"  //s'il a été configuré sur Mosquitto
#define MQTT_PASSWORD "jeedomensacf" //idem

// Time zone 
#define TIMEZONE 1
#define SUMMERTIME 0    // pour heure d'ete et 0 heure d'hivers - utilise pour la gestion d'heure de secours

//mot de passe pour les modification de configuration via la page Web
//et autoriser la mise à jour sans fil OTA
#define PASSWORD_WEB "leti1999"

#endif