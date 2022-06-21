#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <ESP8266WiFi.h>
#include <Param.h>
  
#define MODEL_SENSOR_SHT30 		1
#define MODEL_SENSOR_DHT12 		2
#define MODEL_SENSOR_DHT11 		3
#define MODEL_SENSOR_DHT21 		4
#define MODEL_SENSOR_DHT22 		5
#define MODEL_SENSOR_DS18B20 	6
#define MODEL_SENSOR_BMP180 	7
#define MODEL_SENSOR_BH1750 	8

#ifdef SENSOR_SHT30
#if not defined( DATATEMP)
  #define DATATEMP
#elif not defined(DATATEMP2)
  #define DATATEMP2
#else 
  #define DATATEMP3
#endif

#ifndef DATAHUMIDITY
  #define DATAHUMIDITY
#elif not defined(DATAHUMIDITY2)
  #define DATAHUMIDITY2
#else
  #define DATAHUMIDITY3
#endif
#endif

#ifdef SENSOR_DHT12
#ifndef DATATEMP
  #define DATATEMP
#elif not defined(DATATEMP2)
  #define DATATEMP2
#else 
  #define DATATEMP3
#endif

#ifndef DATAHUMIDITY
  #define DATAHUMIDITY
#elif not defined(DATAHUMIDITY2)
  #define DATAHUMIDITY2
#else
  #define DATAHUMIDITY3
#endif
#endif

#ifdef SENSOR_DHT11
#ifndef DATATEMP
  #define DATATEMP
#elif not defined(DATATEMP2)
  #define DATATEMP2
#else 
  #define DATATEMP3
#endif

#ifndef DATAHUMIDITY
  #define DATAHUMIDITY
#elif not defined(DATAHUMIDITY2)
  #define DATAHUMIDITY2
#else
  #define DATAHUMIDITY3
#endif
#endif

#ifdef SENSOR_DHT21
#ifndef DATATEMP
  #define DATATEMP
#elif not defined(DATATEMP2)
  #define DATATEMP2
#else 
  #define DATATEMP3
#endif

#ifndef DATAHUMIDITY
  #define DATAHUMIDITY
#elif not defined(DATAHUMIDITY2)
  #define DATAHUMIDITY2
#else
  #define DATAHUMIDITY3
#endif
#endif

#ifdef SENSOR_DHT22
#ifndef DATATEMP
  #define DATATEMP
#elif not defined(DATATEMP2)
  #define DATATEMP2
#else 
  #define DATATEMP3
#endif

#ifndef DATAHUMIDITY
  #define DATAHUMIDITY
#elif not defined(DATAHUMIDITY2)
  #define DATAHUMIDITY2
#else
  #define DATAHUMIDITY3
#endif
#endif

#ifdef SENSOR_DS18B20
#ifndef DATATEMP
  #define DATATEMP
#elif not defined(DATATEMP2)
  #define DATATEMP2
#else 
  #define DATATEMP3
#endif
#endif

#ifdef SENSOR_BMP180
#ifndef DATATEMP
  #define DATATEMP
#elif not defined(DATATEMP2)
  #define DATATEMP2
#else 
  #define DATATEMP3
#endif

#ifndef DATAPRESSURE
  #define DATAPRESSURE
#elif not defined(DATAPRESSURE2)
  #define DATAPRESSURE2
#else
  #define DATAPRESSURE3
#endif
#endif

//Capteur de lumière
#ifdef SENSOR_BH1750
#ifndef DATALIGHT
  #define DATALIGHT
#elif not defined(DATALIGHT2)
  #define DATALIGHT2
#else
  #define DATALIGHT3
#endif
#endif

#define TYPE_CAPTEURTEMP 1
#define TYPE_CAPTEURHUMI 2
#define TYPE_CAPTEURPRES 3
#define TYPE_CAPTEURLIGH 4

//Capteurs Tension / Ampere

/* topics */
#define TOPIC               "sensor/capteur"	//entete MQTT
#define LED_TOPIC           "/led" /* 1=on, 0=off */
#define TEMP_TOPIC          "/temperature"
#define TEMP2_TOPIC         "/temperature2"
#define TEMP3_TOPIC         "/temperature3"
#define HYDRO_TOPIC         "/humidity"
#define HYDRO2_TOPIC        "/humidity2"
#define HYDRO3_TOPIC        "/humidity3"
#define PRESSURE_TOPIC      "/presure"
#define PRESSURE2_TOPIC     "/presure2"
#define PRESSURE3_TOPIC     "/presure3"
#define LIGHT_TOPIC         "/light"
#define LIGHT2_TOPIC        "/light2"
#define LIGHT3_TOPIC        "/light3"
#define IP_TOPIC            "/ip"
#define TIME_TOPIC          "/time"
#define VERSION_TOPIC       "/version"
#define ERROR_CAPTEUR_TOPIC "/capteurerror"

#define COMPTEMP_TOPIC "/comptemp" // 0.00 °C
#define COMPTEMP2_TOPIC "/comptemp2" // 0.00 °C
#define COMPTEMP3_TOPIC "/comptemp3" // 0.00 °C
#define COMPHUMIDITY_TOPIC "/comphumidity" // 000 %
#define COMPHUMIDITY2_TOPIC "/comphumidity2" // 000 %
#define COMPHUMIDITY3_TOPIC "/comphumidity3" // 000 %
#define COMPLIGHT_TOPIC "/complight" // 0.00 lux
#define COMPLIGHT2_TOPIC "/complight2" // 0.00 lux
#define COMPLIGHT3_TOPIC "/complight3" // 0.00 lux
#define COMPPRESURE_TOPIC "/comppressure" // 0.00 HPas
#define COMPPRESURE2_TOPIC "/comppressure2" // 0.00 HPas
#define COMPPRESURE3_TOPIC "/comppressure3" // 0.00 HPas
#define REFALTITUDE_TOPIC "/altitude" // 380.00 m
#define TIMEZONE_TOPIC "/timezone" //
#define SUMMERTIME_TOPIC "/summertime" //0 non, 1 oui 
#define MQTT_TOPIC "/mqtt"
#define REBOOT_TOPIC "/reboot" 
#define NUMSONDE_TOPIC "/numsonde" 
#define MQTTADDRESS_TOPIC "/mqttaddress" 
#define RESETMQTTADDRESS_TOPIC "/erasemqttadr"

typedef struct record_data_sensor
  {
      int Type;
	  int Model;
	  int NumCapteur;
      float Value;
      float SumValue;
	  float SensorReading;
	  char Text[5];
	  char CapteurType[20];
  };
  
#endif