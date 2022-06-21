/* hardwaremanager -- 
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

#include "settings.h"

#include <hardwaremanager.h>
#include <Arduino.h>
#include "data.h"

HardwareManager hardwaremanager;

#ifdef SCREEN
#define OLED_RESET 0  // GPIO0
Adafruit_SSD1306 display(OLED_RESET);
#endif

/***************************************/
/* Initialisation Screen               */
/***************************************/

/***************************************/
void HardwareManager::initScreen(char* version) {
/***************************************/

  Serial.println("Screen Init");

#ifdef SCREEN
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

    // Clear the buffer.
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.setTextColor(WHITE);

  display.println("Ver: ");
  display.println(version);
#endif

  char msgTopic[50];
  
  strcpy(msgTopic,"CPT");
  strcat(msgTopic,data.CapteurID);

  strcpy(data.CapteurName,"CPT");
  strcat(data.CapteurName,data.CapteurID);
  
#ifdef SCREEN
  display.println(msgTopic);  
  display.display();
#endif
}


/***************************************/
void HardwareManager::ScreenConnect(void) {
/***************************************/

 #ifdef SCREEN
  display.clearDisplay();

  // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,2);
  display.println("connection");
  display.println("");
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println("WIFI");

  display.display();
 
#endif
}