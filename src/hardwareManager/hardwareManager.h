/* hardwareManager -- 
 *
 * Copyright 2021 Jean-philippe GOI
 * 
 */

/*********************************************************************************/
/*                                                                               */
/*                   hardwareManage                                              */
/*                                                                               */
/*  version    Date        Description                                           */
/*    1.0      03/01/21                                                          */
/*                                                                               */
/*																																							 */
/*********************************************************************************/


#ifndef HARDWAREMANAGER_H
#define HARDWAREMANAGER_H

#include <Arduino.h>

#include <Wire.h>

#include "settings.h"

class HardwareManager
{

public:
	void initScreen(char* version);
	void ScreenConnect(void);
};

extern HardwareManager hardwaremanager;

/*************************************************/
/*     Declaration matÃ©riel                      */
/*************************************************/

/***********************************/
/* Ecran   :  OLED                 */
/*            64x48                */
/*            0.66''               */
/***********************************/

#ifdef SCREEN
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#endif

/***********************************/
/* Capteur :                       */
/*              Temperature        */
/*              Hygrometrie        */
/***********************************/

#ifdef SENSOR_SHT30
#include <WEMOS_SHT3X.h>
#endif

/***********************************/
/* Capteur :                       */
/*              Temperature        */
/*              Hygrometrie        */
/***********************************/

#ifdef SENSOR_DHT12
#include <WEMOS_DHT12.h>
//#include <DHT12.h>
#endif

/***********************************/
/* Capteur :                       */
/*              Temperature        */
/*              Hygrometrie        */
/***********************************/

#ifdef SENSOR_DHT11
#include "DHT.h"

#define DHT11PIN D4     // what digital pin we're connected to

#define DHT11TYPE DHT11   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

#endif

/***********************************/
/* Capteur :                       */
/*              Temperature        */
/*              Hygrometrie        */
/***********************************/

#ifdef SENSOR_DHT21
#include "DHT.h"

#define DHT21PIN D4     // what digital pin we're connected to

#define DHT21TYPE DHT21   // DHT 21 (AM2301)
#endif

/***********************************/
/* Capteur :                       */
/*              Temperature        */
/*              Hygrometrie        */
/***********************************/

#ifdef SENSOR_DHT22
#include "DHT.h"

#define DHT22PIN D4     // what digital pin we're connected to

#define DHT22TYPE DHT22   // DHT 21 (AM2301)

#endif


/***********************************/
/* Capteur :                       */
/*              Temperature        */
/***********************************/

#ifdef SENSOR_DS18B20
#include <OneWire.h>
#include <DallasTemperature.h>
#endif

/***********************************/
/* Capteur :                       */
/*              LuminositÃ©e        */
/***********************************/

#ifdef SENSOR_BH1750
#include <BH1750.h>
#endif

/***********************************/
/* Capteur :                       */
/*              Temperature        */
/*              Barometre          */
/***********************************/

#ifdef SENSOR_BMP180
#include <Adafruit_BMP085.h>
#endif

/***********************************/
/* DataLogger                      */
/*              Horloge Temp RÃ©el  */
/*              Lecteur Micro SD   */
/***********************************/

#ifdef DATALOGGER
// CONNECTIONS:
// DS1307 SDA --> SDA
// DS1307 SCL --> SCL
// DS1307 VCC --> 5v
// DS1307 GND --> GND

#define countof(a) (sizeof(a) / sizeof(a[0]))

#include <RtcDS1307.h>

#include "SD.h"
#include"SPI.h"

#endif

/***************************************/
/* Initialisation Screen               */
/***************************************/

#ifdef SCREEN
extern Adafruit_SSD1306 display;
#endif

#endif
