/* varioLog -- 
 *
 * Copyright 2020 Jean-philippe GOI
 * 
 */

/*********************************************************************************/
/*                                                                               */
/*                           WebSite                                             */
/*                                                                               */
/*  version    Date        Description                                           */
/*    1.0      11/11/20                                                          */
/*    1.0.1    10/01/21    Modification CapteurID et ip serveur mqtt             */
/*    1.0.2    21/01/21    Modif gestion eeprom                                  */
/*                                                                               */
/*																																							 */
/*********************************************************************************/


#ifndef WEBSITE_H
#define WEBSITE_H

#include <Arduino.h>
#include "settings.h"
#include <ESP8266WebServer.h>

/***********************************/
/* Page WEB                        */
/***********************************/

extern ESP8266WebServer server;

extern void handleRoot(void);
extern void HandleReboot(void);
extern void ShowClientResponse(void);
extern void HandleClient(void);
extern void HandleResetParam(void);

#endif
