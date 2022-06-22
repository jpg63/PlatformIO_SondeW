/************************************************************/
/*                     S O N D E . I N O                    */
/*                                                          */
/* par Jean-Philippe GOI                                    */
/*                                                          */
/* 25/08/2018 - 2021                                        */
/************************************************************/
/* Wemos ESP8266                                            */
/*                                                          */
/* Type de carte : Wemos D1 & R2 mini                       */
/*                 Wemos D1 mini Pro (antenne ext           */
/* Flash size    : 4M (1M SPIFFS                            */
/* Debug port    : Serial                                   */
/* CPU Frequency : 80Mhz                                    */
/* Upload Speed  : 921600                                   */
/*                                                          */
/************************************************************/
/*                                                          */
/* Capteurs :                                               */
/* SENSOR_SHT30    temperature+humidite                     */
/* SENSOR_DHT12    temperature+humidite                     */
/* SENSOR_DS18B20  temperature                              */
/* SENSOR_BMP180   temperature+pression atmos               */
/* SENSOR_DHT11    temperature+humidite                     */
/* SENSOR_DHT22    temperature+humidite                     */  
/* SENSOR_DHT21    temperature+humidite                     */
/*                                                          */
/* SENSOR_BH1750  Liminosite                                */
/*                                                          */
/************************************************************/
/*                                                          */
/* Options:                                                 */
/*                                                          */
/* Ecran OLed 0.66'                                         */
/* DataLogger  - CardSD + RTC                               */
/*                                                          */
/************************************************************/
/* Fichier de paramettrage :                                */
/*                                                          */
/* setting\param.h                                          */
/*                                                          */
/************************************************************/
/*                                                          */
/* Web serveur     http://IP_du_capteur                     */
/*                                                          */
/* Ip Fixe / DHCP                                           */
/* DHCP //#define IP_FIXE    Ligne commentÃ©e               */
/*                                                          */
/************************************************************/
/*                                                          */
/* PUBLISH TOPIC MQTT                                       */
/*                                                          */
/* Il est possible d'utiliser MQTTLens sur                  */
/* google chrome ou tout autre client MQTT pour             */
/* mettre Ã  jour les sondes                                */
/*                                                          */
/* compensation via TOPIC MQTT                              */
/* /comptemp        compenssation de temperature            */
/* /comphumidity    compenssation d'humiditÃ©               */
/* /complight       compenssation de lumiÃ¨re               */
/* /comppressure    compenssation de pression               */
/*                                                          */
/*  #Valeur         Compensation absolue                    */
/*                  compensation = valeur                   */
/*  %Valeur         Compensation par difference             */ 
/*                  Comp = valeur mesure - valeur           */
/*   Valeur         Compensation relative                   */  
/*                  Comp = Comp + valeur                    */
/*                                                          */
/*   valeur peut Ãªtre positive ou negative                 */
/*                                                          */   
/* Example                                                  */
/*  sensor/capteur02/comptemp      1.2                      */
/*                                                          */
/* Mise Ã  jour des paramettres de la sonde                 */
/*                                                          */
/* /timezone        1 pour la france                        */
/*                                                          */
/* /summertime      1 pour l'heure d'ete                    */
/*                  0 pour l'heure d'hiver                  */
/*                                                          */
/* /mqtt            0 desactive l'envoi des                 */
/*                    topics MQTT                           */
/*                  1 active l'envoi des topics             */
/*                                                          */
/* /numsonde        0-99 Numero de la sonde                 */
/*                                                          */
/* /reboot          Reboot la sonde                         */
/*                                                          */
/* /mqttaddress     Adresse serveur mqtt                    */
/*                                                          */
/* /erasemqttadr    supprime adresse ip mqtt serveur        */
/*                                                          */
/************************************************************/
/* Topic MQTT                                               */
/*                                                          */
/* sensor/capteur      entete MQTT                          */
/* 02                  numero du capteur                    */
/* /temperature        temperature                          */
/* /humidity           humiditÃ©                            */
/* /presure            pression atmos.                      */
/* /light              luminositÃ©                          */
/* /ip                 adresse ip                           */
/* /time               heure d'acquisition                  */
/* /version            version du logiciel                  */ 
/* /capteurerror       code d'erreur                        */
/*                                                          */
/************************************************************/
/*                                                          */
/* Moyenne des mesures                                      */
/*                                                          */
/* NB_MESURE   Nombre de mesure avant                       */
/*             affichage OLED                               */
/*                                                          */
/* COMPTEUR_MQTT   Envoi tout les MQTT                      */
/*                 COMPTEUR_MQTT X NB_MESURE                */
/*                 mesures                                  */
/*                                                          */
/************************************************************/
/*                                                          */
/* EEProm                                                   */
/*                                                          */
/* 12345                  integer                           */
/* comptemp1              float                             */
/* comptemp2              float                             */
/* comptemp3              float                             */
/* comphumidite1          float                             */
/* comphumidite2          float                             */
/* comphumidite3          float                             */
/* complight1             float                             */
/* complight2             float                             */
/* complight3             float                             */
/* comppressure1          float                             */
/* comppressure2          float                             */
/* comppressure3          float                             */
/* timezone               integer                           */
/* summertime             integer                           */
/* nbreboot               integer                           */
/* numsonde               integer                           */
/* mqttaddress            string[15]                        */
/*                                                          */
/************************************************************/
/*                                                          */
/*  compte wifi generique : jeedom / jeedom                 */
/*                                                          */
/*                                                          */
/************************************************************/
/*                                                          */
/* Version   Description                                    */
/*                                                          */
/* 1.04                 Ajout Transmition heure d'acquisit. */
/*                      Ajout transmition IP                */
/*                                               */
/* 1.05                 Ajout rotation de l'affichage       */
/*                                                          */
/* 1.06                 Ajout Multi capteur                 */
/*                      Correction bug capteur              */
/*                      changement librairie DHT11, DHT22   */
/*                      Ajout Topic MQTT 'Version'          */
/*                                                          */
/* 1.07                 Changement de librairie             */
/*                      Ajout reconnection WIFI et MQTT     */
/*                      Ajout Topic RESET                   */
/*                      Amélioration de la page Web         */
/*                      Gestion synchro ntp                 */
/*                      Gestion auto heure d'été/heure d'hiv*/
/*                      Ajout d'une page Web parametre      */
/*                            http://ip_sonde/parametre     */
/*                      Utilisation de Bootstrap            */
/*                                                          */
/* 1.07b                Correction bug reconnexion wifi     */
/*                                                          */
/* 1.08      01/09/2018                                     */
/*                      Ajout mise à jour sans fil Wifi     */
/*                      OTA via l'interface IDE             */
/*                                                          */
/* 1.09      22/09/2018                                     */
/*                      Ajout gestion des erreurs           */
/*                                                          */
/* 1.09a     13/11/2018                                     */
/*                      Maj librairie                       */   
/* 1.09b     28/11/2018                                     */
/*                      Correction bug "capteurerror"       */    
/* 1.09c     31/10/2020                                     */
/*                      Mise à jours lib                    */
/* 1.10      01/11/20                                       */
/*                      Ajout WifiMulti                     */
/*                      Ajout paramètrage numero sonde      */
/*                      Ajout parametrage wifi et serveur   */
/*                      wifi via la page web                */ 
/*                      Ajout commande /numsonde            */
/*           08/01/21                                       */
/*                      Rename /reset en /reboot            */
/*                      correction numcapteur               */
/*                      ajout ip serveur mqtt               */
/*           21/01/21   Modification gestion eeprom         */
/************************************************************/

// Bibliotheque arduino IDE pour Esp8266
// http://arduino.esp8266.com/stable/package_esp8266com_index.json


// https://randomnerdtutorials.com/esp32-esp8266-input-data-html-form/
//https://byfeel.info/wemos-ep8266-et-serveur-web-dynamique/
//https://tutos-gameserver.fr/2019/10/12/comprendre-la-programmation-web-server-avec-le-code-arduino-%E2%80%A2-projets-diy-bien-choisir-son-serveur-d-impression/

//#include <Arduino.h>

#include <ArduinoOTA.h>

#include <Wire.h>

#include <EEPROM.h>

/*************************************************/
/*     Fichier de configuration                  */
/*************************************************/

#include "settings.h"
#include "website.h"
#include "webserver.h"

#include "data.h"

#define VERSION       "01.10"

String Version = VERSION;

/*   Gestion des Erreur               */


#include <ErrorManager.h>

ErrorManager errormanager;

int nbreboot = 0;

#include "hardwareManager.h"

/***************************************/
/* Initialisation Capteur              */
/***************************************/

#ifdef SENSOR_SHT30
SHT3X sht30(0x45);
#endif

#ifdef SENSOR_DHT12
  DHT12 dht;
#endif

#ifdef SENSOR_DHT11
// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHT11PIN, DHT11TYPE);
#endif

#ifdef SENSOR_DHT21
DHT dht(DHT21PIN, DHT21TYPE);
#endif

#ifdef SENSOR_DHT22
DHT dht(DHT22PIN, DHT22TYPE);
#endif

#ifdef SENSOR_DS18B20
// Data wire is conntec to the Arduino digital pin 2
#define ONE_WIRE_BUS 4

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);
#endif

#ifdef SENSOR_BH1750
BH1750 lightMeter;
#endif

#ifdef SENSOR_BMP180
Adafruit_BMP085 bmp;
#endif

/**************************************/
/* Initialisation RTC                 */
/* Initialisation SDCARD              */
/**************************************/

#ifdef DATALOGGER
RtcDS1307<TwoWire> Rtc(Wire);
/* for normal hardware wire use above */

const char dataTime[] = "what time is it";

//
//the hardware CS pin (10 on most Arduino boards,
// 53 on the Mega) must be left as an output or the SD
// library functions will not work.
const int CSpin = D8;
String dataString =""; // holds the data to be written to the SD card
File sensorData;
String FileName;
#endif

float sensorReading1 = 0.00; // value read from your first sensor
float sensorReading2 = 0.00; // value read from your second sensor
float sensorReading3 = 0.00; // value read from your third sensor
float sensorReading4 = 0.00; // value read from your third sensor

/**********************************************/
/*              S E T U P                     */
/**********************************************/
 
void setup() {

  
  Serial.begin(115200);
  delay(4000);
  Serial.println("Initialisation");
  Serial.println("Booting");
  Serial.flush();

  errormanager.Begin();

  webserver.init();

  dataApp.init();

  char msgTopic[50];
  
  hardwaremanager.initScreen(VERSION);
  
#ifdef DATALOGGER
  FileName = String(dataApp.CapteurName)+".CSV";
#endif

  Serial.print("Version : ");
  Serial.println(+VERSION);

/*  
//  Serial.println(floatingpoint_variable,7);
//  Serial.println(integer_variable);
  Serial.print("Comptemp : " );
  Serial.println(dataApp.CompensationTemp);
  Serial.print("Comptemp2 : " );
  Serial.println(dataApp.CompensationTemp2);
  Serial.print("Comptemp3 : " );
  Serial.println(dataApp.CompensationTemp3);
  Serial.print("CompHumidite : " );
  Serial.println(dataApp.CompensationHumidity);
  Serial.print("CompHumidite2 : " );
  Serial.println(dataApp.CompensationHumidity2);
  Serial.print("CompHumidite3 : " );
  Serial.println(dataApp.CompensationHumidity3);
  Serial.print("CompLight : " );
  Serial.println(dataApp.CompensationLight);
  Serial.print("CompLight2 : " );
  Serial.println(dataApp.CompensationLight2);
  Serial.print("CompLight3 : " );
  Serial.println(dataApp.CompensationLight3);
  Serial.print("CompPressure : " );
  Serial.println(dataApp.CompensationPressure);
  Serial.print("CompPressure2 : " );
  Serial.println(dataApp.CompensationPressure2);
  Serial.print("CompPressure2 : " );
  Serial.println(dataApp.CompensationPressure2);
  Serial.print("TimeZone : " );
  Serial.println(webserver.timezone);
  Serial.print("SummerTime : " );
  Serial.println(webserver.summertime);
  Serial.print("Sonde Number : " );
  Serial.println(dataApp.sondeNumber);
  Serial.print("Sonde ID : " );
  Serial.println(dataApp.CapteurID);

  Serial.flush();*/

  dataApp.readEeproom();
  
  delay(1000);

  hardwaremanager.ScreenConnect();
      
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the BUILTIN_LED pin as an output

  
  //Connection WIFI
  
  webserver.wificonnected = webserver.setup_wifi();

#ifdef SCREEN

  if (webserver.wificonnected) {
    
    webserver.Status[0] = 'W';

    display.clearDisplay();

    // text display tests
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,2);
    display.println("IP Adress");
    display.println("");
    display.println(WiFi.localIP());
    display.display();
    delay(4000);
  
    display.clearDisplay();

    // text display tests
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,2);
    display.println("connection");
    display.println("");
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.println("MQTT");

    display.display();
  }
 
#endif

if (webserver.wificonnected) {
  // Connection MQTT

    int CompteurTestConnection = 0;
    String tmpSSID = WiFi.SSID();

    Serial.print("Wifi SSID : ");
    Serial.println(tmpSSID);
      
    Serial.print("Serveur MQTT : ");
    if (String(webserver.mqtt_server4) != "") 
    {
      client.setServer(webserver.mqtt_server4, 1883);
      Serial.println(webserver.mqtt_server4);   
      Serial.println("Serveur MQTT Config Web");
    }    
    else if (tmpSSID == SSID1) {
      client.setServer(webserver.mqtt_server1, 1883);
      Serial.println(webserver.mqtt_server1);   
    }
    else if (tmpSSID == SSID2) {
      client.setServer(webserver.mqtt_server2, 1883);
      Serial.println(webserver.mqtt_server2);   
    }
    else if (tmpSSID == SSID3) {
      client.setServer(webserver.mqtt_server3, 1883);
      Serial.println(webserver.mqtt_server3);   
    }
    else  {
      client.setServer("", 1883);
      Serial.println("");   
      Serial.println("Erreur SSID non trouve");
    }

    client.setCallback(callback);
    while ((!client.connected()) && (CompteurTestConnection < 5)) {
      webserver.reconnect();
      CompteurTestConnection++;
      Serial.print("CompteurTestConnection : ");
      Serial.println(CompteurTestConnection);   
    }   
  }

 if (!client.connected()) {
      Serial.println("MQTT not Connected");
      webserver.Status[2] = '_';
      webserver.mqttconnected = false;   
    } 
    else
    {
      Serial.println("MQTT Connected");
      webserver.Status[2] = 'M';
      webserver.mqttconnected = true;   
    }

 
//Demarrage serveur web
  Serial.println("Demarrage Serveur Web");

  // On branche la fonction qui gÃ¨re la premiere page / link to the function that manage launch page 
  server.on ( "/", handleRoot );
//  server.on ("/Sauve", handleSave);
  server.on("/parametre", HandleClient); // The client connected with no arguments e.g. http:192.160.0.40/
  server.on("/resetparam", HandleResetParam); // The client connected with no arguments e.g. http:192.160.0.40/
  server.on("/result", ShowClientResponse);
  server.on("/reboot", HandleReboot);  
  server.on("/upgrade", HTTP_POST, []() {
      server.sendHeader("Connection", "close");
      server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
      ESP.restart();
    }, []() {
      HTTPUpload& upload = server.upload();
      if (upload.status == UPLOAD_FILE_START) {
        Serial.setDebugOutput(true);
        WiFiUDP::stopAll();
        Serial.printf("Update: %s\n", upload.filename.c_str());
        uint32_t maxSketchSpace = (ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000;
        if (!Update.begin(maxSketchSpace)) { //start with max available size
          Update.printError(Serial);
        }
      } else if (upload.status == UPLOAD_FILE_WRITE) {
        if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
          Update.printError(Serial);
        }
      } else if (upload.status == UPLOAD_FILE_END) {
        if (Update.end(true)) { //true to set the size to the current progress
          Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
        } else {
          Update.printError(Serial);
        }
        Serial.setDebugOutput(false);
      }
      yield();
    });
 
  server.begin();
  Serial.println ( "HTTP server started" );

#ifdef SENSOR_DS18B20
  sensors.begin();
#endif  

#ifdef SENSOR_BH1750
lightMeter.begin();
Serial.println("BH1750 Test begin");
#endif

#ifdef SENSOR_BMP180
  if (!bmp.begin()) {
    Serial.println("Could not find BMP180 or BMP085 sensor at 0x77");
  }
#endif

#ifdef SENSOR_DHT12
//  dht12.begin();
#endif

#ifdef SENSOR_DHT11
//    dht.setup(DHT11PIN, DHTesp::DHT11); // Connect DHT sensor to GPIO 2
  dht.begin();
#endif

#ifdef SENSOR_DHT21
  dht.begin();
#endif

#ifdef SENSOR_DHT22
//#define DHTTYPE DHT22     
  dht.begin();
#endif

int nbcapteurtemp = 1;
int nbcapteurhumi = 1;
int nbcapteurligh = 1;
int nbcapteurpres = 1;

strcpy(dataApp.CapteurList,"Capteur : ");

#ifdef SENSOR_SHT30
    Serial.println("Init SHT30");
    Serial.print("nbcapteur : ");
    Serial.println(dataApp.nbcapteur);
    
    strcpy(dataApp.CapteurType,"SHT30");
    if (strlen(dataApp.CapteurList) < 11)  strcat(dataApp.CapteurList,"SHT30");
    else                                strcat(dataApp.CapteurList,",SHT30");

    strcpy(dataApp.Tableaufifo[dataApp.nbcapteur].CapteurType,"SHT30");
    dataApp.Tableaufifo[dataApp.nbcapteur].Model = MODEL_SENSOR_SHT30;   
    dataApp.Tableaufifo[dataApp.nbcapteur].Type = TYPE_CAPTEURTEMP;
    dataApp.Tableaufifo[dataApp.nbcapteur].NumCapteur = nbcapteurtemp++;
    strcpy(dataApp.Tableaufifo[dataApp.nbcapteur].Text,"T:");
    dataApp.nbcapteur++;
    
    strcpy(dataApp.Tableaufifo[dataApp.nbcapteur].CapteurType,"SHT30");
    dataApp.Tableaufifo[dataApp.nbcapteur].Model = MODEL_SENSOR_SHT30;
    dataApp.Tableaufifo[dataApp.nbcapteur].Type = TYPE_CAPTEURHUMI;
    dataApp.Tableaufifo[dataApp.nbcapteur].NumCapteur = nbcapteurhumi++;
    strcpy(dataApp.Tableaufifo[dataApp.nbcapteur].Text,"H:");
    dataApp.nbcapteur++;
#endif  

#ifdef SENSOR_DHT12
    Serial.println("Init DHT12");
    Serial.print("nbcapteur : ");
    Serial.println(dataApp.nbcapteur);

    strcpy(dataApp.CapteurType,"DHT12");
    if (strlen(dataApp.CapteurList) < 11)  strcat(dataApp.CapteurList,"DHT12");
    else                                strcat(dataApp.CapteurList,",DHT12");
    
    strcpy(dataApp.Tableaufifo[dataApp.nbcapteur].CapteurType,"DHT12");
    dataApp.Tableaufifo[dataApp.nbcapteur].Model = MODEL_SENSOR_DHT12;     
    dataApp.Tableaufifo[dataApp.nbcapteur].Type = TYPE_CAPTEURTEMP;
    if (nbcapteurtemp == 1)      strcpy(dataApp.Tableaufifo[dataApp.nbcapteur].Text,"T:");
    else if (nbcapteurtemp == 2) strcpy(dataApp.Tableaufifo[dataApp.nbcapteur].Text,"T2:");
    else                         strcpy(dataApp.Tableaufifo[dataApp.nbcapteur].Text,"T3:");
    dataApp.Tableaufifo[dataApp.nbcapteur].NumCapteur = nbcapteurtemp++;
    dataApp.nbcapteur++;
    
    strcpy(dataApp.Tableaufifo[dataApp.nbcapteur].CapteurType,"DHT12");
    dataApp.Tableaufifo[dataApp.nbcapteur].Model = MODEL_SENSOR_DHT12;     
    dataApp.Tableaufifo[dataApp.nbcapteur].Type = TYPE_CAPTEURHUMI;
    if (nbcapteurhumi == 1)      strcpy(dataApp.Tableaufifo[dataApp.nbcapteur].Text,"H:");
    else if (nbcapteurhumi == 2) strcpy(dataApp.Tableaufifo[dataApp.nbcapteur].Text,"H2:");
    else                         strcpy(dataApp.Tableaufifo[dataApp.nbcapteur].Text,"H3:");
    dataApp.Tableaufifo[dataApp.nbcapteur].NumCapteur = nbcapteurhumi++;
    dataApp.nbcapteur++;
    
#endif  

#ifdef SENSOR_DHT11
    Serial.println("Init DHT11");
    Serial.print("nbcapteur : ");
    Serial.println(dataApp.nbcapteur);

    strcpy(dataApp.CapteurType,"DHT11");
    if (strlen(dataApp.CapteurList) < 11) strcat(dataApp.CapteurList,"DHT11");
    else                               strcat(dataApp.CapteurList,",DHT11");

    strcpy(dataApp.Tableaufifo[dataApp.nbcapteur].CapteurType,"DHT11");
    dataApp.Tableaufifo[dataApp.nbcapteur].Model = MODEL_SENSOR_DHT11;        
    dataApp.Tableaufifo[dataApp.nbcapteur].Type = TYPE_CAPTEURTEMP;
    if (nbcapteurtemp == 1)      strcpy(dataApp.Tableaufifo[dataApp.nbcapteur].Text,"T:");
    else if (nbcapteurtemp == 2) strcpy(dataApp.Tableaufifo[dataApp.nbcapteur].Text,"T2:");
    else                         strcpy(dataApp.Tableaufifo[dataApp.nbcapteur].Text,"T3:");
    dataApp.Tableaufifo[dataApp.nbcapteur].NumCapteur = nbcapteurtemp++;
    dataApp.nbcapteur++;
    
    strcpy(dataApp.Tableaufifo[dataApp.nbcapteur].CapteurType,"DHT11");
    dataApp.Tableaufifo[dataApp.nbcapteur].Model = MODEL_SENSOR_DHT11;     
    dataApp.Tableaufifo[dataApp.nbcapteur].Type = TYPE_CAPTEURHUMI;
    if (nbcapteurhumi == 1)      strcpy(dataApp.Tableaufifo[dataApp.nbcapteur].Text,"H:");
    else if (nbcapteurhumi == 2) strcpy(dataApp.Tableaufifo[dataApp.nbcapteur].Text,"H2:");
    else                         strcpy(dataApp.Tableaufifo[dataApp.nbcapteur].Text,"H3:");
    dataApp.Tableaufifo[dataApp.nbcapteur].NumCapteur = nbcapteurhumi++;
    dataApp.nbcapteur++;
#endif  

#ifdef SENSOR_DHT21
    Serial.println("Init DHT21");
    Serial.print("nbcapteur : ");
    Serial.println(dataApp.nbcapteur);

    strcpy(CapteurType,"DHT21");
    if (strlen(dataApp.CapteurList) < 11)  strcat(dataApp.CapteurList,"DHT21");
    else                                strcat(dataApp.CapteurList,",DHT21");

    strcpy(dataApp.Tableaufifo[dataApp.nbcapteur].CapteurType,"DHT21");
    dataApp.Tableaufifo[dataApp.nbcapteur].Model = MODEL_SENSOR_DHT21;           
    Tableaufifo[dataApp.nbcapteur].Type = TYPE_CAPTEURTEMP;
    if (nbcapteurtemp == 1)      strcpy(dataApp.Tableaufifo[dataApp.nbcapteur].Text,"T:");
    else if (nbcapteurtemp == 2) strcpy(dataApp.Tableaufifo[dataApp.nbcapteur].Text,"T2:");
    else                         strcpy(dataApp.Tableaufifo[dataApp.nbcapteur].Text,"T3:");
    dataApp.Tableaufifo[dataApp.nbcapteur].NumCapteur = nbcapteurtemp++;
    dataApp.nbcapteur++;
    
    strcpy(dataApp.Tableaufifo[nbcapteur].CapteurType,"DHT21");
    dataApp.Tableaufifo[dataApp.nbcapteur].Model = MODEL_SENSOR_DHT21;        
    Tableaufifo[nbcapteur].Type = TYPE_CAPTEURHUMI;
    if (nbcapteurhumi == 1)      strcpy(Tableaufifo[nbcapteur].Text,"H:");
    else if (nbcapteurhumi == 2) strcpy(Tableaufifo[nbcapteur].Text,"H2:");
    else                         strcpy(Tableaufifo[nbcapteur].Text,"H3:");
    Tableaufifo[nbcapteur].NumCapteur = nbcapteurhumi++;
    nbcapteur++;
#endif  

#ifdef SENSOR_DHT22
    Serial.println("Init DHT22");
    Serial.print("nbcapteur : ");
    Serial.println(nbcapteur);

    strcpy(CapteurType,"DHT22");
    if (strlen(CapteurList) < 11) strcat(CapteurList,"DHT22");
    else                          strcat(CapteurList,",DHT22");

    strcpy(Tableaufifo[nbcapteur].CapteurType,"DHT22");
    Tableaufifo[nbcapteur].Model = MODEL_SENSOR_DHT22;           
    Tableaufifo[nbcapteur].Type = TYPE_CAPTEURTEMP;
    if (nbcapteurtemp == 1)      strcpy(Tableaufifo[nbcapteur].Text,"T:");
    else if (nbcapteurtemp == 2) strcpy(Tableaufifo[nbcapteur].Text,"T2:");
    else                         strcpy(Tableaufifo[nbcapteur].Text,"T3:");
    Tableaufifo[nbcapteur].NumCapteur = nbcapteurtemp++;
    nbcapteur++;
    
    strcpy(Tableaufifo[nbcapteur].CapteurType,"DHT22");
    Tableaufifo[nbcapteur].Model = MODEL_SENSOR_DHT22;           
    Tableaufifo[nbcapteur].Type = TYPE_CAPTEURHUMI;
    if (nbcapteurhumi == 1)      strcpy(Tableaufifo[nbcapteur].Text,"H:");
    else if (nbcapteurhumi == 2) strcpy(Tableaufifo[nbcapteur].Text,"H2:");
    else                         strcpy(Tableaufifo[nbcapteur].Text,"H3:");
    Tableaufifo[nbcapteur].NumCapteur = nbcapteurhumi++;
    nbcapteur++;
#endif  

#ifdef SENSOR_DS18B20
    Serial.println("Init DS18B2");
    Serial.print("nbcapteur : ");
    Serial.println(nbcapteur);

    strcpy(CapteurType,"DS18B2");
    if (strlen(CapteurList) < 11) strcat(CapteurList,"DS18B2");
    else                          strcat(CapteurList,",DS18B2");

    strcpy(Tableaufifo[nbcapteur].CapteurType,"DS18B");
    Tableaufifo[nbcapteur].Model = MODEL_SENSOR_DS18B20;           
    Tableaufifo[nbcapteur].Type = TYPE_CAPTEURTEMP;
    if (nbcapteurtemp == 1)      strcpy(Tableaufifo[nbcapteur].Text,"T:");
    else if (nbcapteurtemp == 2) strcpy(Tableaufifo[nbcapteur].Text,"T2:");
    else                         strcpy(Tableaufifo[nbcapteur].Text,"T3:");
    Tableaufifo[nbcapteur].NumCapteur = nbcapteurtemp++;
    nbcapteur++;
#endif  

#ifdef SENSOR_BMP180
    Serial.println("Init BMP180");
    Serial.print("nbcapteur : ");
    Serial.println(nbcapteur);

    strcpy(CapteurType,"BMP180");
 
    strcpy(Tableaufifo[nbcapteur].CapteurType,"BMP18");
    Tableaufifo[nbcapteur].Model = MODEL_SENSOR_BMP180;           
    Tableaufifo[nbcapteur].Type = TYPE_CAPTEURTEMP;
    if (nbcapteurtemp == 1)      strcpy(Tableaufifo[nbcapteur].Text,"T:");
    else if (nbcapteurtemp == 2) strcpy(Tableaufifo[nbcapteur].Text,"T2:");
    else                         strcpy(Tableaufifo[nbcapteur].Text,"T3:");
    Tableaufifo[nbcapteur].NumCapteur = nbcapteurtemp++;
    nbcapteur++;
 
    strcpy(Tableaufifo[nbcapteur].CapteurType,"BMP18");
    Tableaufifo[nbcapteur].Model = MODEL_SENSOR_BMP180;           
    Tableaufifo[nbcapteur].Type = TYPE_CAPTEURPRES;
    if (nbcapteurpres == 1)      strcpy(Tableaufifo[nbcapteur].Text,"P:");
    else if (nbcapteurpres == 2) strcpy(Tableaufifo[nbcapteur].Text,"P2:");
    else                         strcpy(Tableaufifo[nbcapteur].Text,"P3:");
    Tableaufifo[nbcapteur].NumCapteur = nbcapteurpres++;
    nbcapteur++;
#endif  

#ifdef SENSOR_BH1750
    Serial.println("Init BH1750");
    Serial.print("nbcapteur : ");
    Serial.println(nbcapteur);


    strcpy(CapteurType,"BH1750");
    if (strlen(CapteurList) < 11) strcat(CapteurList,"BH1750");
    else                          strcat(CapteurList,",BH1750");
    
    strcpy(Tableaufifo[nbcapteur].CapteurType,"BH175");
    Tableaufifo[nbcapteur].Model = MODEL_SENSOR_BH1750;           
    Tableaufifo[nbcapteur].Type = TYPE_CAPTEURLIGH;
    if (nbcapteurligh == 1)      strcpy(Tableaufifo[nbcapteur].Text,"L:");
    else if (nbcapteurligh == 2) strcpy(Tableaufifo[nbcapteur].Text,"L2:");
    else                         strcpy(Tableaufifo[nbcapteur].Text,"L3:");
    Tableaufifo[nbcapteur].NumCapteur = nbcapteurligh++;
    nbcapteur++;
#endif  

#ifdef SCREEN
  display.clearDisplay();

  // text display tests
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,2);
  display.println("capt:");

boolean affichecapteur = true;

#ifdef SENSOR_SHT30
  if (affichecapteur) {
    display.println("SHT30");
    affichecapteur = false;
}
#endif  

#ifdef SENSOR_DHT12
  if (affichecapteur) {
    display.println("DHT12");
    affichecapteur = false;
  }
#endif  

#ifdef SENSOR_DHT11
  if (affichecapteur) {
    display.println("DHT11");
    affichecapteur = false;
  }
#endif  

#ifdef SENSOR_DHT21
  if (affichecapteur) {
    display.println("DHT21");
    affichecapteur = false;
  }
#endif  

#ifdef SENSOR_DHT22
  if (affichecapteur) {
    display.println("DHT22");
    affichecapteur = false;
  }

#endif  

#ifdef SENSOR_DS18B20
  if (affichecapteur) {
    display.println("DS18B");
    affichecapteur = false;
  }
#endif  

#ifdef SENSOR_BMP180
  if (affichecapteur) {
    display.println("BMP18");
    affichecapteur = false;
  }

#endif  

#ifdef SENSOR_BH1750
  if (affichecapteur) {
    display.println("BH175");
    affichecapteur = false;
  }

#endif  

  strcpy(msgTopic,"CPT");
  strcat(msgTopic,dataApp.CapteurID);
  display.println(msgTopic);  

  display.display();
 
#endif


  Serial.print("compiled: ");
  Serial.print(__DATE__);
  Serial.println(__TIME__);

//Gestion enregistrement sur Carte SD et de l'horloge interne

#ifdef dataAppLOGGER

    //--------RTC SETUP ------------
    // if you are using ESP-01 then uncomment the line below to reset the pins to
    // the available pins for SDA, SCL
    // Wire.begin(0, 2); // due to limited pins, use pin 0 and 2 for SDA, SCL
    
    Rtc.Begin();

    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    printDateTime(compiled);
    Serial.println();

    if (!Rtc.IsDateTimeValid()) 
    {
        Serial.println("RTC lost confidence in the DateTime!");
        Rtc.SetDateTime(compiled);
    }

    if (!Rtc.GetIsRunning())
    {
        Serial.println("RTC was not actively running, starting now");
        Rtc.SetIsRunning(true);
    }

    RtcDateTime now = Rtc.GetDateTime();
    if (now < compiled) 
    {
        Serial.println("RTC is older than compile time!  (Updating DateTime)");
        Rtc.SetDateTime(compiled);
    }

    // never assume the Rtc was last configured by you, so
    // just clear them to your needed state
    Rtc.SetSquareWavePin(DS1307SquareWaveOut_Low); 

/* comment out on a second run to see that the info is stored long term */
    // Store something in memory on the RTC
    Rtc.SetMemory(0, 13);
    uint8_t written = Rtc.SetMemory(13, (const uint8_t*)dataApp, sizeof(dataApp) - 1); // remove the null terminator strings add
    Rtc.SetMemory(1, written);
/* end of comment out section */


   Serial.print("Initializing SD card...");
   pinMode(CSpin, OUTPUT);
//
// see if the card is present and can be initialized:
   if (!SD.begin(CSpin)) Serial.println("Card failed, or not present");
   else                  
     {
      
      Serial.print("SD activate");
      Status[4] = 'S';
      Serial.println(Status);
 
      Serial.println("card initialized.");
      // open a new file and immediately close it:
      // Check to see if the file exists:

      if (!SD.exists(FileName)) {
        Serial.println("Creating "+FileName+"...");
        sensorData = SD.open(FileName, FILE_WRITE);

        char datestring1[20];
        char datestring2[20];

        snprintf_P(datestring1, 
            countof(datestring1),
            PSTR("%02u/%02u/%04u"),
            now.Day(),
            now.Month(),          
            now.Year() );
            
        snprintf_P(datestring2, 
            countof(datestring2),
            PSTR("%02u:%02u:%02u"),
            now.Hour(),
            now.Minute(),
            now.Second() );

        dataString = String(datestring1) + "," + String(datestring2) + "," + FileName + "," + ","; // convert to CSV
        sensorData.println(dataString);
        sensorData.close();
      }
     }
#endif
/*  // Démarrage du processus NTP
  NTP.begin (ntpServer, timezone, dayligthSaving, minutesOffset);
  // Interval de synchronisation en seconde (30 min.)
  NTP.setInterval (1800);*/

}


/**********************************************/
/*              L O O P                       */
/**********************************************/


//int Tableaufifotype[8];
//float TableaufifoValue[8];
//int FifoPos = 0;


void loop() {


//TEST WIFI et MQTT

  char msgTopic[50];


  if (WiFi.status() != WL_CONNECTED) {

    errormanager.SetErrorWifi();
    Serial.println("Wifi déconnecté");
    WiFi.disconnect(); 
 //   WiFi.setAutoReconnect ( true );
    webserver.wificonnected = false;
    webserver.Status[0] = '_';
    Serial.println("Mqtt déconnecté");
    webserver.mqttconnected  = false;   
    webserver.wifidesactived = true;
    webserver.Status[2] = '_';
    if (webserver.compteurwifiinactif == 0)
      {
        webserver.compteurwifiinactif++;
        webserver.oldtime = millis();
      }
  }
  else {
     webserver.compteurwifiinactif = 0;
  }

  if ((WiFi.status() == WL_CONNECTED) && (!client.connected())) {
    errormanager.SetErrorMqtt();
    webserver.Status[2] = '_';  
    webserver.mqttconnected = false;   
    Serial.println("Mqtt déconnecté");
    if (webserver.compteurmqttinactif == 0)
      {
        webserver.compteurmqttinactif++;
        webserver.oldtime = millis();
      }
  }
  else {
     webserver.compteurmqttinactif = 0;
  }


#ifdef SCREEN
    display.setTextSize(1);
    display.setCursor(6, 0);
    display.print("    ");
    display.print(String(webserver.Status));
    display.display();
    Serial.println(String(webserver.Status));
#endif

  unsigned long tmptime = millis();
  if (((webserver.wifidesactived) || (!webserver.mqttconnected)) && ((tmptime - webserver.oldtime) > 60000)) {
    
    webserver.oldtime = millis();
    if (!webserver.wificonnected) {
      Serial.println("Test de reconnection Wifi");
      webserver.wificonnected = webserver.setup_wifi();

#ifdef SCREEN

      if (webserver.wificonnected) {
    
        Serial.println("Wifi Reconnecté");
        webserver.Status[0] = 'W';

        display.clearDisplay();
    
        // text display tests
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0,2);
        display.println("IP Adress");
        display.println("");
        display.println(WiFi.localIP());
        display.display();
        delay(4000);
      
        display.clearDisplay();
    
        // text display tests
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0,2);
        display.println("connection");
        display.println("");
        display.setTextSize(2);
        display.setTextColor(WHITE);
        display.println("MQTT");
    
        display.display();
      }
 
#endif    
    }
    
    if ((webserver.wificonnected) && (!webserver.mqttconnected)) {
      // Connection MQTT

        Serial.println("Test de reconnection Mqtt");
    
        int CompteurTestConnection = 0;
    
        while ((!client.connected()) && (CompteurTestConnection < 5)) {
          webserver.reconnect();
          CompteurTestConnection++;
          Serial.print("CompteurTestConnection : ");
          Serial.println(CompteurTestConnection);   
        }   
    
       if (!client.connected()) {
            Serial.println("MQTT not Connected");
            webserver.Status[2] = '_';
            webserver.mqttconnected = false;   
          } 
          else
          {
            Serial.println("MQTT Connected");
            webserver.Status[2] = 'M';
            webserver.mqttconnected = true;   
          }
    }

    if ((webserver.wificonnected) && (webserver.wifidesactived)) {
    
      //Demarrage serveur web
      Serial.println("Demarrage Serveur Web");
    
      // On branche la fonction qui gÃ¨re la premiere page / link to the function that manage launch page 
      server.on ( "/", handleRoot );
      server.on("/parametre", HandleClient); // The client connected with no arguments e.g. http:192.160.0.40/
      server.on("/result", ShowClientResponse);
       
      server.begin();
      Serial.println ( "HTTP server started" );

      webserver.wifidesactived = false;
    }
  }
  
    
  //Mesures
  
  dataApp.compteurMesure++;
  int compteurPosTableau=0;
  Serial.print("nbcapteur : ");
  Serial.println(dataApp.nbcapteur);
  
  while(compteurPosTableau < dataApp.nbcapteur) {
    
    float Mesure;
  
  
    Serial.print("compteurPosTableau : ");
    Serial.println(compteurPosTableau);
    Serial.print("Model : ");
    Serial.println(dataApp.Tableaufifo[compteurPosTableau].Model);
    
    if (dataApp.Tableaufifo[compteurPosTableau].Model == MODEL_SENSOR_SHT30) 
      {
       Serial.println("read Data SHT30");
  
  #ifdef SENSOR_SHT30
       if(sht30.get()==0)
         {
           Mesure = sht30.cTemp;
           dataApp.MesureMajTemp(Mesure, compteurPosTableau++);
  
           Mesure    = sht30.humidity;
           dataApp.MesureMajHumidity(Mesure, compteurPosTableau); 
         }
         else {
           Serial.println("Error SHT30!");
           errormanager.SetErrorCapteur();
           dataApp.Tableaufifo[compteurPosTableau++].Value   = 999;
         }
 #endif
      }   
      else if (dataApp.Tableaufifo[compteurPosTableau].Model == MODEL_SENSOR_DHT11) 
        { 
          Serial.println("read Data DHT11");
  
  #ifdef SENSOR_DHT11
          Mesure = dht.readTemperature();
          dataApp.MesureMajTemp(Mesure, compteurPosTableau++);
  
          Mesure = dht.readHumidity();
          dataApp.MesureMajHumidity(Mesure, compteurPosTableau);
  #endif
        }
       else if (dataApp.Tableaufifo[compteurPosTableau].Model == MODEL_SENSOR_DHT21) {
         Serial.println("read Data DHT21");
  
  #ifdef SENSOR_DHT21
         Mesure = dht.readTemperature();
         MesureMajTemp(Mesure, compteurPosTableau++);
  
         Mesure = dht.readHumidity();
         MesureMajHumidity(Mesure, compteurPosTableau);
  #endif
       }
       else if (dataApp.Tableaufifo[compteurPosTableau].Model == MODEL_SENSOR_DHT22) {
         Serial.println("read Data DHT22");
  
  #ifdef SENSOR_DHT22
  
    //delay(dht.getMinimumSamplingPeriod());
  
         Mesure = dht.readTemperature();
         MesureMajTemp(Mesure, compteurPosTableau++);
  
         Mesure = dht.readHumidity();
         MesureMajHumidity(Mesure, compteurPosTableau);
  #endif
       }
       else if (dataApp.Tableaufifo[compteurPosTableau].Model == MODEL_SENSOR_DHT12) {
         Serial.println("read Data DHT12");
  
  #ifdef SENSOR_DHT12
        if(dht.get()==0){
          Mesure = dht.cTemp;
          Serial.println(Mesure);
          dataApp.MesureMajTemp(Mesure, compteurPosTableau++);
  
          Mesure = dht.humidity;
          Serial.println(Mesure);
          dataApp.MesureMajHumidity(Mesure, compteurPosTableau);
        }
        else {
           Serial.println("Error DHT12!");
           errormanager.SetErrorCapteur();
           dataApp.Tableaufifo[compteurPosTableau++].Value   = 999;
        }
  #endif
       }
      else if (dataApp.Tableaufifo[compteurPosTableau].Model == MODEL_SENSOR_DS18B20) {
         Serial.println("read Data DS18B20");
  
  #ifdef SENSOR_DS18B20
         sensors.requestTemperatures(); 
         Mesure = sensors.getTempCByIndex(0);
         dataApp.MesureMajTemp(Mesure, compteurPosTableau);
  #endif
       }
       else if (dataApp.Tableaufifo[compteurPosTableau].Model == MODEL_SENSOR_BH1750) {
        Serial.println("read Data BH1750");
  #ifdef SENSOR_BH1750
  
         Mesure = lightMeter.readLightLevel();
         dataApp.MesureMajLight(Mesure, compteurPosTableau);
  #endif
       }
       else if (dataApp.Tableaufifo[compteurPosTableau].Model == MODEL_SENSOR_BMP180) {
         Serial.println("read Data BMP180");
  
  #ifdef SENSOR_BMP180
         Mesure = bmp.readTemperature();
         dataApp.MesureMajTemp(Mesure, compteurPosTableau++);
  
         Mesure = bmp.readPressure() / 100;
         dataApp.MesureMajPressure(Mesure, compteurPosTableau);
  #endif
       }
  
    compteurPosTableau++;
  }

// NTP et Date/Time

  if (webserver.wificonnected) {

    server.handleClient();

    NTP.onNTPSyncEvent ([](NTPSyncEvent_t event) {
      webserver.processNtpEvent(event);
    });

    Serial.print("Date et heure d'envoi MQTT : ");
    Serial.print(NTP.getDateStr());
    Serial.print(" - ");
    Serial.println(NTP.getTimeStr());
    strcpy(webserver.timemesure,NTP.getDateStr().c_str ());
    strcat(webserver.timemesure," - ");
    strcat(webserver.timemesure,NTP.getTimeStr().c_str ());
  }
  else
  {
   strcpy(webserver.timemesure,"jj/mm/aaaa - hh:mm");
  }

  if (webserver.wificonnected) {
    ArduinoOTA.handle();
  }

#ifdef DATALOGGER
  time_t now = time(nullptr);
  Serial.print("timemesure : ");
  Serial.println(ctime(&now));
  if ((!webserver.wificonnected) || (ErrorEventNTP)) {  strcpy(webserver.timemesure,ctime(&now)); }
#endif

// affiche page web

  if (webserver.wificonnected) {
    
    Serial.println("WifiHandle -------------------------------------");

    Serial.flush();
  
  }
   
  //Gestion de l'Ã©cran OLED
  
  if (dataApp.compteurMesure >= NB_MESURE) {
  
    Serial.println("Affichage");
    Serial.println(dataApp.compteurMesure);
  
    for (int i=0;i<dataApp.nbcapteur;i++) {
      dataApp.Tableaufifo[i].SensorReading += dataApp.Tableaufifo[i].SumValue/dataApp.compteurMesure;
    }
  /*#ifdef DATATEMP
       sensorReading1 += TempValue/compteurMesure;
  #endif
  
  #ifdef DATAHUMIDITY
     sensorReading2 += HumidityValue/compteurMesure;
  #endif
  
  #ifdef DATALIGHT
     sensorReading3 += LightValue/compteurMesure;
  #endif
  
  #ifdef DATAPRESSION
     sensorReading4 += PressureValue/compteurMesure;
  #endif*/


#ifdef SCREEN 

//Effacement OLED
  
  // Clear the buffer.
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.setTextColor(WHITE);

//int nbcapteur = 0;
//int compteuraff = 0;
  int compteurrot = 0;

  while ((compteurrot < 2) && (compteurrot < dataApp.nbcapteur))
    {
     switch (dataApp.Tableaufifo[dataApp.FifoPos+compteurrot].Type) {
    
       case TYPE_CAPTEURTEMP :
         display.setTextSize(1);
         display.println(dataApp.Tableaufifo[dataApp.FifoPos+compteurrot].Text);
         display.setTextSize(2);
         display.println(dataApp.Tableaufifo[dataApp.FifoPos+compteurrot].SumValue/dataApp.compteurMesure);  
         break;
       case TYPE_CAPTEURHUMI :
       case TYPE_CAPTEURLIGH :
       case TYPE_CAPTEURPRES :
         display.setTextSize(1);
         display.println(dataApp.Tableaufifo[dataApp.FifoPos+compteurrot].Text);
         display.setTextSize(2);
         display.println(int(dataApp.Tableaufifo[dataApp.FifoPos+compteurrot].SumValue/dataApp.compteurMesure));  
         break;
       default:
         break;
      }
   
     compteurrot++; 
    }

    dataApp.FifoPos++;
    if (dataApp.FifoPos+1 >= dataApp.nbcapteur) dataApp.FifoPos = 0;

#endif

    for (int i=0; i<dataApp.nbcapteur; i++) dataApp.Tableaufifo[i].SumValue = 0; 
    //float TempValue;
    //TempValue = 0;
    dataApp.HumidityValue = 0;
    dataApp.LightValue = 0;
    dataApp.PressureValue = 0;
    dataApp.compteurMesure = 0;
    webserver.compteurMqtt++;
  }


//Envoi les mesures au serveur MQTT

if (webserver.compteurMqtt >= COMPTEUR_MQTT) {
  
  Serial.println("Envoi Topic Mqtt");
//  Serial.println(compteurMqtt);

  Serial.print("Date et heure d'envoi MQTT : ");
  Serial.print(NTP.getDateStr());
  Serial.print(" - ");
  Serial.println(NTP.getTimeStr());
  strcpy(webserver.timemesure,NTP.getDateStr().c_str ());
  strcat(webserver.timemesure," - ");
  strcat(webserver.timemesure,NTP.getTimeStr().c_str ());

#ifndef DATALOGGER
  time_t now = time(nullptr);
  Serial.print("timemesure : ");
  Serial.println(ctime(&now));
  if ((!webserver.wificonnected) || (webserver.ErrorEventNTP)) {  strcpy(webserver.timemesure,ctime(&now)); }
#endif

/*  sensorReading1 = sensorReading1 / compteurMqtt;
  sensorReading2 = sensorReading2 / compteurMqtt;
  sensorReading3 = sensorReading3 / compteurMqtt;
  sensorReading4 = sensorReading4 / compteurMqtt;*/
 for (int i=0;i<dataApp.nbcapteur;i++) {
    dataApp.Tableaufifo[i].SensorReading = dataApp.Tableaufifo[i].SensorReading / webserver.compteurMqtt;
  }

  webserver.compteurMqtt = 0;

#ifdef DATALOGGER
    if (!Rtc.IsDateTimeValid()) 
    {
        // Common Cuases:
        //    1) the battery on the device is low or even missing and the power line was disconnected
        Serial.println("RTC lost confidence in the DateTime!");
    }

    RtcDateTime now = Rtc.GetDateTime();

    printDateTime(now);
    Serial.println();

//    delay(5000);

    // read data

    // get the offset we stored our data from address zero
    uint8_t address = Rtc.GetMemory(0);
    if (address != 13)
    {
        Serial.println("address didn't match");
    }
    else
    {
        // get the size of the data from address 1
        uint8_t count = Rtc.GetMemory(1);
        uint8_t buff[20];

        // get our data from the address with the given size
        uint8_t gotten = Rtc.GetMemory(address, buff, count);

        if (gotten != count ||
            count != sizeof(dataApp) - 1) // remove the extra null terminator strings add
        {
            Serial.print("something didn't match, count = ");
            Serial.print(count, DEC);
            Serial.print(", gotten = ");
            Serial.print(gotten, DEC);
            Serial.println();
        }
        Serial.print("data read (");
        Serial.print(gotten);
        Serial.print(") = \"");
        while (gotten > 0)
        {
            Serial.print((char)buff[count - gotten]);
            gotten--;
        }
        Serial.println("\"");
    } 
#endif

    for (int i=0;i<dataApp.nbcapteur;i++) {
      Serial.println("Boucle capteur");
      switch (dataApp.Tableaufifo[i].Type) {
    
      case TYPE_CAPTEURTEMP :
        if (!isnan(dataApp.Tableaufifo[i].SensorReading)) {
          sprintf (dataApp.msgTemperature, "%5.2lf", dataApp.Tableaufifo[i].SensorReading);
          /* publish the message */

          strcpy(msgTopic,TOPIC);
          strcat(msgTopic,dataApp.CapteurID);
          if (dataApp.Tableaufifo[i].NumCapteur == 1)      strcat(msgTopic,TEMP_TOPIC);
          else if (dataApp.Tableaufifo[i].NumCapteur == 2) strcat(msgTopic,TEMP2_TOPIC);
          else                                          strcat(msgTopic,TEMP3_TOPIC);

          Serial.print("MsgTopic : ");
          Serial.println(msgTopic);

          if ((webserver.wificonnected) && (webserver.mqtt_enable)) {
            if (client.connected())  {
              Serial.println("Envoi au serveur MQTT");
              client.publish(msgTopic, dataApp.msgTemperature);
            }
          }
          Serial.print("Mqtt Temperature : ");
          Serial.println(dataApp.msgTemperature);
          Serial.flush();
        }       
        break;
      case TYPE_CAPTEURHUMI :
        if (!isnan(dataApp.Tableaufifo[i].SensorReading)) {
          sprintf (dataApp.msgHumidite, "%2.0lf", dataApp.Tableaufifo[i].SensorReading);
          strcpy(msgTopic,TOPIC);
          strcat(msgTopic,dataApp.CapteurID);
          if (dataApp.Tableaufifo[i].NumCapteur == 1)      strcat(msgTopic,HYDRO_TOPIC);
          else if (dataApp.Tableaufifo[i].NumCapteur == 2) strcat(msgTopic,HYDRO2_TOPIC);
          else                                          strcat(msgTopic,HYDRO3_TOPIC);

          /* publish the message */
          if ((webserver.wificonnected) && (webserver.mqtt_enable)) {
            if (client.connected()) client.publish(msgTopic, dataApp.msgHumidite);
          }
          Serial.print("Mqtt HumiditÃ© : ");
          Serial.println(dataApp.msgHumidite);      
        }        
        break;
      case TYPE_CAPTEURLIGH :
        if (!isnan(dataApp.Tableaufifo[i].SensorReading)) {
          sprintf (dataApp.msgLight, "%i", dataApp.Tableaufifo[i].SensorReading);
          /* publish the message */
          strcpy(msgTopic,TOPIC);
          strcat(msgTopic,dataApp.CapteurID);
          if (dataApp.Tableaufifo[i].NumCapteur == 1)      strcat(msgTopic,LIGHT_TOPIC);
          else if (dataApp.Tableaufifo[i].NumCapteur == 2) strcat(msgTopic,LIGHT2_TOPIC);
          else                                          strcat(msgTopic,LIGHT3_TOPIC);
  
          if ((webserver.wificonnected) && (webserver.mqtt_enable)) {
            if (client.connected())  client.publish(msgTopic, dataApp.msgLight);
          }
          Serial.print("Mqtt Light : ");
          Serial.println(dataApp.msgLight);
          Serial.flush();
        }
        break;
      case TYPE_CAPTEURPRES :
        if (!isnan(dataApp.Tableaufifo[i].SensorReading)) {
          sprintf (dataApp.msgPressure, "%i", dataApp.Tableaufifo[i].SensorReading);
          /* publish the message */

          strcpy(msgTopic,TOPIC);
          strcat(msgTopic,dataApp.CapteurID);
          if (dataApp.Tableaufifo[i].NumCapteur == 1)      strcat(msgTopic,PRESSURE_TOPIC);
          else if (dataApp.Tableaufifo[i].NumCapteur == 2) strcat(msgTopic,PRESSURE2_TOPIC);
          else                                          strcat(msgTopic,PRESSURE3_TOPIC);
 
          if ((webserver.wificonnected) && (webserver.mqtt_enable)) {
            if (client.connected())  client.publish(msgTopic, dataApp.msgPressure);
          }
          Serial.print("Mqtt Pressure : ");
          Serial.println(dataApp.msgPressure);
          Serial.flush();
        }      
        break;
      default:
        break;       
      }
    }

     /* publish the message */

   strcpy(msgTopic,TOPIC);
   strcat(msgTopic,dataApp.CapteurID);
   strcat(msgTopic,IP_TOPIC);

   if ((webserver.wificonnected) && (webserver.mqtt_enable)) {
     if (client.connected())  client.publish(msgTopic, webserver.adresseip);
   }
 
  Serial.print("Mqtt Ip : ");
  Serial.println(webserver.adresseip);

  strcpy(msgTopic,TOPIC);
  strcat(msgTopic,dataApp.CapteurID);
  strcat(msgTopic,TIME_TOPIC);

  if ((webserver.wificonnected) && (webserver.mqtt_enable)) {
    if (client.connected())  client.publish(msgTopic, webserver.timemesure);
  }
  Serial.print("Mqtt Time : ");
  Serial.println(webserver.timemesure);

  strcpy(msgTopic,TOPIC);
  strcat(msgTopic,dataApp.CapteurID);
  strcat(msgTopic,VERSION_TOPIC);

  if ((webserver.wificonnected) && (webserver.mqtt_enable)) {
    if (client.connected())  client.publish(msgTopic, VERSION);
  }
  Serial.print("Mqtt Version : ");
  Serial.println(VERSION);
  Serial.flush();

#ifdef DATALOGGER

// build the data string
    char datestring1[20];
    char datestring2[20];

    snprintf_P(datestring1, 
            countof(datestring1),
            PSTR("%02u/%02u/%04u"),
            now.Day(),
            now.Month(),          
            now.Year() );
            
      snprintf_P(datestring2, 
            countof(datestring2),
            PSTR("%02u:%02u:%02u"),
            now.Hour(),
            now.Minute(),
            now.Second() );
     dataString = String(datestring1) + "," + String(datestring2);
#endif

    for (int i=0;i<dataApp.nbcapteur;i++) {

#ifdef DATALOGGER
       dataString += "," + String(dataApp.Tableaufifo[i].SensorReading);
#endif

      dataApp.Tableaufifo[i].SensorReading = 0.00;
/*      sensorReading1 = 0.00; 
      sensorReading2 = 0.00; 
      sensorReading3 = 0.00; 
      sensorReading4 = 0.00;*/
    }

#ifdef DATALOGGER   
    Serial.println(dataString);
    saveData(); // save to SD card
#endif
   }
/*  else
  {
    Serial.println("Error!");
    
#ifdef SCREEN  
    display.println("Error!");
#endif

  }*/
  
#ifdef SCREEN
  display.setTextSize(1);
  display.setCursor(6, 0);
  display.print("    ");
  display.print(String(webserver.Status));
  display.display();
  Serial.println(String(webserver.Status));
#endif

  Serial.flush();

/*  if (wificonnected) {
    if (!client.connected()) {
      reconnect();
    }
    client.loop();
  }*/

  if ((webserver.wificonnected)&& (client.connected())){
    client.loop();
  }

  errormanager.Handle();
  delay(2000);
#ifdef SENSOR_DHT11
  delay(2000);
#endif
}

#ifdef DATALOGGER


/***************************************/
/* P R I N T D A T A T I M E           */
/***************************************/

void printDateTime(const RtcDateTime& dt)
{
    char datestring[20];

    snprintf_P(datestring, 
            countof(datestring),
            PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
            dt.Day(),
            dt.Month(),          
            dt.Year(),
            dt.Hour(),
            dt.Minute(),
            dt.Second() );
    Serial.print(datestring);
    if ((!webserver.wificonnected) || (ErrorEventNTP) {  strcpy(timemesure,datestring); }
}

/**********************************/
/*S A V E D A T A                  */
/**********************************/

void saveData(){
  if(SD.exists(FileName)){ // check the card is still there
    // now append new data file
    sensorData = SD.open(FileName, FILE_WRITE);
    if (sensorData){
      sensorData.println(dataString);
      sensorData.close(); // close the file
      Serial.println("Data writing to file");
    }
  }
  else{
    Serial.println("Error writing to file !");
  }
}
#endif




/*
 Client NTP
Nous allons maintenant ajouter la partie client NTP.

Dans la partie des imports ajoutez la ligne suivante :

#include <TimeLib.h>
#include <NtpClientLib.h>
Dans la partie des variables statiques ajoutez les lignes suivantes :

// Serveur NTP
const char ntpServer[] = "pool.ntp.org";
// Offset depuis UTC
int8_t timeZoneOffset = 0;
// Le fuseau utilise les horaires été / hiver
bool dayligthSaving = true;
// Minutes d'offset à ajouter
int8_t minutesOffset = 0;
A la fin de la fonction setup() nous allons ajouter les lignes suivantes :

// Démarrage du processus NTP
NTP.begin (ntpServer, timeZoneOffset, dayligthSaving, minutesOffset);
// Interval de synchronisation en seconde (30 min.)
NTP.setInterval (1800);
Nous allons créer la fonction printTime:

void printTime(){
  static uint16_t i = 0;
  Serial.printf ("%d %s ", i, NTP.getTimeDateString ().c_str());
  Serial.print (NTP.isSummerTime () ? "Heure d'été. " : "Heure d'hiver. ");
  Serial.printf ("Démarrage le: %s allumé depuis %s\n", NTP.getTimeDateString(NTP.getFirstSync()).c_str(), NTP.getUptimeString().c_str());
  i++;
  delay(5000);
}
Que nous allons appeler dans la fonction loop :

void loop () {
  printTime();
}
Le code précédent vous donne le résultat suivant sur le port série :

0 00:00:01 01/01/1970 Heure d'hiver. Démarrage le: 00:00:00 01/01/1970 allumé depuis    0 days 00:00:09
1 00:00:06 01/01/1970 Heure d'hiver. Démarrage le: 00:00:00 01/01/1970 allumé depuis    0 days 00:00:14
2 00:00:11 01/01/1970 Heure d'hiver. Démarrage le: 00:00:00 01/01/1970 allumé depuis    0 days 00:00:19
Récupérer les événements
Il est possible de récupérer les événements NTP grâce à la fonction onNTPSyncEvent. Pour cela nous allons créer la fonction processNtpEvent :

void processNtpEvent (NTPSyncEvent_t ntpEvent) {
  if (ntpEvent) {
    Serial.print ("Erreur de synchronisation: ");
    if (ntpEvent == noResponse)
      Serial.println ("Serveur NTP injoignable");
    else if (ntpEvent == invalidAddress)
      Serial.println ("Adresse du serveur NTP invalide");
  } else {
    Serial.print ("Récupération du temps NTP: ");
    Serial.println (NTP.getTimeDateString (NTP.getLastNTPSync ()));
  }
}
Nous allons ensuite l'appeler dans la fonction loop:

NTP.onNTPSyncEvent ([](NTPSyncEvent_t event) {
  processNtpEvent(event);
});
Le code précédent vous donne le résultat suivant sur le port série :

Récupération du temps NTP: 22:38:21 18/02/2018
0 22:38:21 18/02/2018 Heure d'hiver. Démarrage le: 22:38:21 18/02/2018 allumé depuis    0 days 00:00:12
Menu de navigation
Se connecterPageDiscussionLireVoir le texte sourceHistoriqueRechercher

Rechercher sur The Linux Craftsman
Accueil
Modifications récentes
Page au hasard
Aide
Outils
Pages liées
Suivi des pages liées
Pages spéciales
Version imprimable
Adresse permanente
Information sur la page
Dernière modification de cette page le 19 février 2018, à 01:06.
 */
