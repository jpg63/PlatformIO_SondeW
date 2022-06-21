/* website -- 
 *
 * Copyright 2020 Jean-philippe GOI
 * 
 */

/*********************************************************************************/
/*                                                                               */
/*                           Website                                             */
/*                                                                               */
/*  version    Date        Description                                           */
/*    1.0      11/11/20                                                          */
/*    1.0.1    10/01/21    Modification CapteurID et ip serveur mqtt             */
/*    1.0.2    21/01/21    Modif gestion eeprom                                  */
/*                                                                               */
/*																																							 */
/*********************************************************************************/

#include <website.h>
#include <Arduino.h>

#include <EEPROM.h>

#include "data.h"
#include "webserver.h"

#include <ErrorManager.h>

ESP8266WebServer server ( 80 );

extern String Version;

String Argument_Name, Clients_Response1, Clients_Response2;

/*****************************/
void handleRoot(){ 
/*****************************/
  String page;  
  int    lignepaire = 0;
  
  page = "<html lang='fr'><head><meta http-equiv='refresh' content='60' name='viewport' content='width=device-width, initial-scale=1'/>";
  page += "<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css'>";
  page += "<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js'></script>";
  page += "<script src='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js'></script>";
  page += "<title>ESP8266 MQTT - Projet Sonde</title></head><body>";
  page += "<div class='container-fluid'>";
  page +=   "<div class='row'>";
  page +=     "<div class='col-md-8'>";
  page +=       "<h1>ESP8266 MQTT</h1>";
  page +=       "<ul class='nav nav-pills'>";
  page +=         "<li class='active'>";
  page +=           "<a href='#'> <span class='badge pull-right'>";
  page +=           data.temperature;
  page +=           "</span> Temp&eacute;rature</a>";
  page +=         "</li><li>";
  page +=           "<a href='#'> <span class='badge pull-right'>";
  page +=           data.humidity;
  page +=           "</span> Humidit&eacute;</a>";
  page +=         "</li><li>";
  page +=           "<a href='#'> <span class='badge pull-right'>";
  page +=           data.pressure;
  page +=           "</span> Pression atmosph&eacute;rique</a></li>";
  page +=       "</ul>";


 /* page += "<div class='row'>";
  page += "<div class='col-xs-3'>.col-sm-4</div>";
  page += "<div class='col-xs-3'>.col-sm-4</div>";
  page += "<div class='col-xs-3'>.col-sm-4</div>";
  page += "</div>";
  page += "<div class='row'>";
  page += "<div class='col-xs-3'>.col-sm-4</div>";
  page += "<div class='col-xs-3'>.col-sm-4</div>";
  page += "<div class='col-xs-3'>.col-sm-4</div>";
  page += "</div>";*/


  page +=       "<div class='table-responsive-sm'>";
  page +=       "<table class='table table-condensed'>";  // Tableau des relevés
  page +=         "<thead><tr><th><h3>Capteur</h3></th><th><h3>Mesure</h3></th><th><h3>Compensation</h3></th></tr></thead>"; //Entête
  page +=         "<tbody>";  // Contenu du tableau
  #ifdef DATATEMP
                    if (lignepaire%2 == 0) page += "<tr>";
                    else               page += "<tr class='active'>";
                    lignepaire++;
  page +=           "<td><h3>Temp&eacute;rature</h3></td><td><h3>"; // Première ligne : température
  page +=             data.temperature;
  page +=             "&deg;C</h3></td><td><h3>";
  page +=             data.CompensationTemp;
  page +=             "</h3></td></tr>";
  #endif
  #ifdef DATATEMP2
                    if (lignepaire%2 == 0) page += "<tr>";
                    else               page += "<tr class='active'>";
                    lignepaire++;
  page +=           "<td><h3>Temp&eacute;rature 2</h3></td><td><h3>"; // Première ligne : température
  page +=             data.temperature2;
  page +=             "&deg;C</h3></td><td><h3>";
  page +=             data.CompensationTemp2;
  page +=             "</h3></td></tr>";
  #endif
  #ifdef DATATEMP3
                    if (lignepaire%2 == 0) page += "<tr>";
                    else               page += "<tr class='active'>";
                    lignepaire++;
  page +=           "<td><h3>Temp&eacute;rature 3</h3></td><td><h3>"; // Première ligne : température
  page +=             data.temperature3;
  page +=             "&deg;C</h3></td><td><h3>";
  page +=             data.CompensationTemp3;
  page +=             "</h3></td></tr>";
  #endif
  
  #ifdef DATAHUMIDITY
                    if (lignepaire%2 == 0) page += "<tr>";
                    else               page += "<tr class='active'>";
                    lignepaire++;
  page +=           "<td><h3>Humidit&eacute;</h3></td><td><h3>"; // 2nd ligne : Humidité
  page +=             data.humidity;
  page +=             "%</h3></td><td><h3>";
  page +=             data.CompensationHumidity;
  page +=             "</h3></td></tr>";
  #endif
  #ifdef DATAHUMIDITY2
                    if (lignepaire%2 == 0) page += "<tr>";
                    else               page += "<tr class='active'>";
                    lignepaire++;
  page +=           "<td><h3>Humidit&eacute; 2</h3></td><td><h3>"; // 2nd ligne : Humidité
  page +=             data.humidity2;
  page +=             "%</h3></td><td><h3>";
  page +=             data.CompensationHumidity2;
  page +=             "</h3></td></tr>";
  #endif
  #ifdef DATAHUMIDITY3
                    if (lignepaire%2 == 0) page += "<tr>";
                    else               page += "<tr class='active'>";
                    lignepaire++;
  page +=           "<td><h3>Humidit&eacute; 3</h3></td><td><h3>"; // 2nd ligne : Humidité
  page +=             data.humidity3;
  page +=             "%</h3></td><td><h3>";
  page +=             data.CompensationHumidity3;
  page +=             "</h3></td></tr>";
  #endif
 
  #ifdef DATAPRESSURE1
                    if (lignepaire%2 == 0) page += "<tr>";
                    else               page += "<tr class='active'>";
                    lignepaire++;
  page +=           "<td><h3>Pression atmosph&eacute;rique</h3></td><td><h3>"; 
  page +=             data.pressure;
  page +=             "mbar</h3></td><td><h3>";
  page +=             data.CompensationPressure;
  page +=             "</h3></td></tr>";
  #endif
  #ifdef DATAPRESSURE2
                    if (lignepaire%2 == 0) page += "<tr>";
                    else               page += "<tr class='active'>";
                    lignepaire++;
  page +=           "<td><h3>Pression atmosph&eacute;rique</h3></td><td><h3>"; 
  page +=             data.pressure2;
  page +=             "mbar</h3></td><td><h3>";
  page +=             data.CompensationPressure2;
  page +=             "</h3></td></tr>";
  #endif
  #ifdef DATAPRESSURE3
                    if (lignepaire%2 == 0) page += "<tr>";
                    else               page += "<tr class='active'>";
                    lignepaire++;
  page +=           "<td><h3>Pression atmosph&eacute;rique</h3></td><td><h3>"; 
  page +=             data.pressure3;
  page +=             "mbar</h3></td><td><h3>";
  page +=             data.CompensationPressure3;
  page +=             "</h3></td></tr>";
  #endif

  #ifdef DATALIGHT
                    if (lignepaire%2 == 0) page += "<tr>";
                    else               page += "<tr class='active'>";
                    lignepaire++;
  page +=           "<td><h3>Lumi&egrave;re</h3></td><td><h3>"; 
  page +=             data.lux;
  page +=             "lux</h3></td><td><h3>";
  page +=             data.CompensationLight;
  page +=             "</h3></td></tr>";
  #endif
  #ifdef DATALIGHT2
                    if (lignepaire%2 == 0) page += "<tr>";
                    else               page += "<tr class='active'>";
                    lignepaire++;
  page +=           "<td><h3>Lumi&egrave;re</h3></td><td><h3>"; 
  page +=             data.lux2;
  page +=             "lux</h3></td><td><h3>";
  page +=             data.CompensationLight2;
  page +=             "</h3></td></tr>";
  #endif
  #ifdef DATALIGHT3
                    if (lignepaire%2 == 0) page += "<tr>";
                    else               page += "<tr class='active'>";
                    lignepaire++;
  page +=           "<td><h3>Lumi&egrave;re</h3></td><td><h3>"; 
  page +=             data.lux3;
  page +=             "lux</h3></td><td><h3>";
  page +=             data.CompensationLight3;
  page +=             "</h3></td></tr>";
  #endif
  
  page +=       "</tbody></table></div>";

/*  page = "<html lang=fr-FR><head><meta http-equiv='refresh' content='60'/>";
  page += "<title>ESP8266 MQTT - Projet Sonde</title>";
//  page += "<style> body { background-color: #fffff; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }</style>";
  page += "<style> body { background-color: #E6E6FA; font-family: Arial, Helvetica, Sans-Serif; Color: blue;}</style>";
  page += "</head><body><h1>ESP8266 MQTT</h1>";*/
  page += "<h3><ul><li><span class='label label-primary'>";
  page += data.CapteurName;
  page += "</span></li></ul></h3>";
/*  page += "<h3><ul><li>";
  page += CapteurType;
  page += "</li></ul></h3>";*/
  page += "<h3><ul><li>Version : <span class='label label-default'>";
  page += Version;
  page += "</span></li></ul></h3>";
  page += "<h3><ul><li>";
  page += data.CapteurList;
  page += "</li></ul></h3>";

  #ifdef SCREEN
  page += "<h3><ul><li>Ecran OLED";
  page += "</li></ul></h3>";  
  #endif

  #ifdef DATALOGGER
  page += "<h3><ul><li>Carte SD + Horloge RTC";
  page += "</li></ul></h3>";  
  #endif
  
/*  #ifdef DATATEMP
  page += "<ul><li>Temperature : ";
  page += temperature;
  page += "&ordm;C - (";
  page += CompensationTemp;
  page += ")</li></ul>";
  #endif
  #ifdef DATATEMP2
  page += "<ul><li>Temperature 2 : ";
  page += temperature2;
  page += "&ordm;C - (";
  page += CompensationTemp2;
  page += ")</li></ul>";
  #endif
  #ifdef DATATEMP3
  page += "<ul><li>Temperature 3 : ";
  page += temperature3;
  page += "&ordm;C - (";
  page += CompensationTemp3;
  page += ")</li></ul>";
  #endif
  #ifdef DATAHUMIDITY
  page += "<ul><li>Humidite : ";
  page += humidity;
  page += "% - (";
  page += CompensationHumidity;
  page += ")</li></ul>";
  #endif
  #ifdef DATAHUMIDITY2
  page += "<ul><li>Humidite 2 : ";
  page += humidity2;
  page += "% - (";
  page += CompensationHumidity2;
  page += ")</li></ul>";
  #endif  
  #ifdef DATAHUMIDITY3
  page += "<ul><li>Humidite 3 : ";
  page += humidity3;
  page += "% - (";
  page += CompensationHumidity3;
  page += ")</li></ul>";
  #endif
  #ifdef DATAPRESSURE
  page += "<ul><li>Pression atmospherique : ";
  page += pressure;
  page += " hPa - (";
  page += CompensationPressure;
  page += ")</li></ul>";
  #endif
  #ifdef DATAPRESSURE2
  page += "<ul><li>Pression atmospherique 2 : ";
  page += pressure2;
  page += " hPa - (";
  page += CompensationPressure2;
  page += ")</li></ul>";
  #endif  
  #ifdef DATAPRESSURE3
  page += "<ul><li>Pression atmospherique 3 : ";
  page += pressure3;
  page += " hPa - (";
  page += CompensationPressure3;
  page += ")</li></ul>";
  #endif
  #ifdef DATALIGHT
  page += "<ul><li>Lumi&egrave;re : ";
  page += lux;
  page += " lux - (";
  page += CompensationLight;
  page += ")</li></ul>";
  #endif
  #ifdef DATALIGHT2
  page += "<ul><li>Lumi&egrave;re : ";
  page += lux;
  page += " lux - (";
  page += CompensationLight;
  page += ")</li></ul>";
  #endif
  #ifdef DATALIGHT3
  page += "<ul><li>Lumi&egrave;re : ";
  page += lux;
  page += " lux - (";
  page += CompensationLight;
  page += ")</li></ul>";
  #endif*/
  page += "<h3><ul><li>Date et Heure : <span class='label label-default'>";
  page += webserver.timemesure;
  page += "</span></li></ul></h3>";

 /* page += "<h1><ul><li>Parametrage";
  page += "</li></ul></h1>";
  page += "<ul><li><h3>Compensation de Temperature</h3>";
  page += "<input type='number' name='comptemp1' id='comptemp1' placeholder='";
  page += CompensationTemp;
  page += "' size=2 step='0.1' min='-10.00' max='+10.00'> - ";
  page += "<input type='number' name='comptemp2' id='comptemp2' placeholder='";
  page += CompensationTemp2;
  page += "' size=2 step='0.1'> - ";
  page += "<input type='number' name='comptemp3' id='comptemp3' placeholder='";
  page += CompensationTemp3;
  page += "' size=2 step='0.1'>";
  page += "</li></ul>";

  page += "<ul><li><h3>Compensation d'Hygrometrie</h3>";
  page += "<input type='number' name='comphygro1' id='comphygro1' placeholder='";
  page += CompensationHumidity;
  page += "' size=2 step='0.1'> - ";
  page += "<input type='number' name='comphygro2' id='comphygro2' placeholder='";
  page += CompensationHumidity2;
  page += "' size=2 step='0.1'> - ";
  page += "<input type='number' name='comphygro3' id='comphygro3' placeholder='";
  page += CompensationHumidity3;
  page += "' size=2 step='0.1'>";
  page += "</li></ul>";

  page += "<ul><li><h3>Compensation Luminosite</h3>";
  page += "<input type='number' name='complight1' id='complight1' placeholder='";
  page += CompensationLight;
  page += "' size=2 step='0.1'> - ";
  page += "<input type='number' name='complight2' id='complight2' placeholder='";
  page += CompensationLight2;
  page += "' size=2 step='0.1'> - ";
  page += "<input type='number' name='complight3' id='complight3' placeholder='";
  page += CompensationLight3;
  page += "' size=2 step='0.1'>";
  page += "</li></ul>";

  page += "<ul><li><h3>Compensation de Pression</h3>";
  page += "<input type='number' name='comppressure1' id='comppressure1' placeholder='";
  page += CompensationPressure;
  page += "' size=2 step='0.1'> - ";
  page += "<input type='number' name='comppressure2' id='comppressure2' placeholder='";
  page += CompensationPressure2;
  page += "' size=2 step='0.1'> - ";
  page += "<input type='number' name='comppressure3' id='comppressure3' placeholder='";
  page += CompensationPressure3;
  page += "' size=2 step='0.1'>";
  page += "</li></ul>";

  page += "<ul><li><h3>Time Zone</h3>";
  page += "<input type='number' name='timezone' id='timezone' placeholder='";
  page += timezone;
  page += "' size=2 step='0.1'>";
  page += "</li></ul>";

  page += "<ul><li>";
  page += "<input type='checkbox' name='heuredete' value='heuredete'> Heure d'ete<br>";
  page += "</li></ul>";

  page += "<ul><li><h3>Mot de passe</h3>";
  page += "<input type='password' name='psw' id='psw'>";
  page += "</li></ul>";

 // page += "<div>";
  page += "<ul><br>";
//  page += "<button id=\'save_button\'>Save</button>";
  page += "<INPUT type='submit' value='Actualiser'>";
  page += "</ul>";*/
 
//  page += "<INPUT type='submit' value='Actualiser'>";
  String IPaddress = WiFi.localIP().toString();

  page += "<br><div class='py-5'>";
    page += "<div class='container'>";
      page += "<div class='row'>";
        page += "<div class='col-ml-12'>";
          page += "<a class='btn btn-info btn-lg' href='http://"+IPaddress+"/parametre'>Parametrage </a>"+"   ";
          page += "<a class='btn btn-info btn-lg' href='http://"+IPaddress+"/update'>Update </a>" + "   ";
          page += "<a class='btn btn-info btn-lg' href='http://"+IPaddress+"/reboot'>Reboot </a>";
        page += "</div>";
      page += "</div>";
    page += "</div>";
  page += "</div>";
  
/*   page += "<form action='http://"+IPaddress+"/parametre'>";
   page += "<input type='submit' value='Parametrage' />";
   page += "</form>";*/
   
 // page += "<br><p><a href='http://"+IPaddress+"/parametre'>          Parametrage</a></p>";

  page += "<br><h4><p><a href='https://jeedom2.clermont-fd.archi.fr'>          Jeedom</a></p></h4>";
  page += "<h4><p><a href='http://jeedom2.clermont-fd.archi.fr:3000'>          Grafana</a></p></h4>";
  page += "</div></div></div>";
  page += "</body></html>";
    server.send ( 200, "text/html", page );
}

/********************************************/
void HandleClient() {
/********************************************/
  
  boolean SauveParam = false;
  String webpage;

  webpage = "<html lang='fr'><head><meta http-equiv='refresh' content='60' name='viewport' content='width=device-width, initial-scale=1'/>";
  webpage += "<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css'><script src='https://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js'></script><script src='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js'></script>";
  webpage += "<title>ESP8266 MQTT - Parametrage</title></head><body>";
  webpage += "<div class='container-fluid'>";
  webpage +=   "<div class='row'>";
  webpage +=     "<div class='col-md-8'>";
  webpage +=       "<h1>ESP8266 MQTT - Parametrage</h1>";

/*  webpage =  "<html lang=fr-FR><meta http-equiv='refresh' content='60'/>";
  webpage += "<head><title>ESP8266 MQTT - Projet Sonde</title>";
  webpage += "<style>";
  webpage += "body { background-color: #E6E6FA; font-family: Arial, Helvetica, Sans-Serif; Color: blue;}";
  webpage += "</style>";
  webpage += "</head>";
  webpage += "<body>";


  webpage += "<h1><br>ESP8266 MQTT - Parametrage</h1>";*/
  webpage += "<TD><h3>Nom &nbsp;: ";
  webpage += data.CapteurName;
  webpage += "<br>";
  webpage += data.CapteurList;
  webpage += "</h3>";
  #ifdef DATATEMP
  webpage += "Temperature &nbsp;: ";
  Serial.print("Temperature   : ");
  Serial.println(data.temperature);
  webpage += data.temperature;
  webpage += "&ordm;C - (";
  webpage += data.CompensationTemp;
  webpage += ")<br>";
  #endif
  #ifdef DATATEMP2
  webpage += "Temperature 2 &nbsp;: ";
  webpage += data.temperature2;
  webpage += "&ordm;C - (";
  webpage += data.CompensationTemp2;
  webpage += ")<br>";
  #endif
  #ifdef DATATEMP3
  webpage += "Temperature 3 &nbsp;: ";
  webpage += data.temperature3;
  webpage += "&ordm;C - (";
  webpage += data.CompensationTemp3;
  webpage += ")<br>";
  #endif
  #ifdef DATAHUMIDITY
  webpage += "Humidite &nbsp;: ";
  webpage += data.humidity;
  webpage += "% - (";
  webpage += data.CompensationHumidity;
  webpage += ")<br>";
  #endif
  #ifdef DATAHUMIDITY2
  webpage += "Humidite 2 &nbsp;: ";
  webpage += data.humidity2;
  webpage += "% - (";
  webpage += data.CompensationHumidity2;
  webpage += ")<br>";
  #endif  
  #ifdef DATAHUMIDITY3
  webpage += "Humidite 3 &nbsp;: ";
  webpage += data.humidity3;
  webpage += "% - (";
  webpage += data.CompensationHumidity3;
  webpage += ")<br>";
  #endif
  #ifdef DATAPRESSURE
  webpage += "Pression atmospherique &nbsp;: ";
  webpage += data.pressure;
  webpage += " hPa - (";
  webpage += data.CompensationPressure;
  webpage += ")<br>";
  #endif
  #ifdef DATAPRESSURE2
  webpage += "Pression atmospherique 2 &nbsp;: ";
  webpage += data.pressure2;
  webpage += " hPa - (";
  webpage += data.CompensationPressure2;
  webpage += ")<br>";
  #endif  
  #ifdef DATAPRESSURE3
  webpage += "Pression atmospherique 3 &nbsp;: ";
  webpage += data.pressure3;
  webpage += " hPa - (";
  webpage += data.CompensationPressure3;
  webpage += ")<br>";
  #endif
  #ifdef DATALIGHT
  webpage += "Lumi&egrave;re &nbsp;: ";
  webpage += data.lux;
  webpage += " lux - (";
  webpage += data.CompensationLight;
  webpage += ")<br>";
  #endif
  #ifdef DATALIGHT2
  webpage += "Lumi&egrave;re 2 &nbsp;: ";
  webpage += data.lux2;
  webpage += " lux - (";
  webpage += data.CompensationLight2;
  webpage += ")<br>";
  #endif
  #ifdef DATALIGHT3
  webpage += "Lumi&egrave;re 3 &nbsp;: ";
  webpage += data.lux3;
  webpage += " lux - (";
  webpage += data.CompensationLight3;
  webpage += ")<br>";
  #endif
  webpage += "Date et Heure : ";
  webpage += webserver.timemesure;
  webpage += "<br>";
   
  String IPaddress = WiFi.localIP().toString();
  webpage += "Adresse IP : ";
  webpage += IPaddress;
  webpage += "<br>";

//  webpage += "<br><p><a href='http://"+IPaddress+"'>          Retour</a></p>";
  webpage += "<a class='btn btn-info btn-mg' href='http://"+IPaddress+"'>Retour </a>";

  webpage += "<div class='py-5'>";
  webpage += "<div class='container'>";
  webpage += "<div class='row'>";
  webpage += "<div class='col-sm-2'><h4>Mot de passe</h4></div>";
  webpage += "<div class='col-sm-3'>";
  webpage += "<input type='Maj pwd' name='psw' id='psw'>";
  webpage += "</div></div></div>";

  webpage += "<form action='http://"+IPaddress+"/parametre' method='POST'>";
/*  webpage += "&nbsp;&nbsp;&nbsp;&nbsp;Please enter your Name:<input type='text' name='name_input'><BR>";
  webpage += "Please enter your Address:<input type='text' name='address_input'>&nbsp;";*/
  webpage += "<h4><input type='submit' value='SAUVEGARDE'></h4>"; // omit <input type='submit' value='Enter'> for just 'enter'

  webpage += "<form action='http://"+IPaddress+"/resetparam' method='POST'>";
  webpage += "<h4><input type='submit' value='RESET'></h4>"; // omit <input type='submit' value='Enter'> for just 'enter'


  webpage +=       "<div class='table-responsive'>";
  webpage +=       "<table class='table table-condensed'>";  // Tableau des relevés
  webpage +=         "<thead><tr><th><h4>Type</h4></th><th><h4>Capteur 1</h4></th><th><h4>Capteur 2</h4></th><th><h4>Capteur 3</h4></th></tr></thead>"; //Entête
  webpage +=         "<tbody>";  // Contenu du tableau
  webpage +=           "<tr><td><h4>Temp&eacute;rature</h4></td><td><h4>"; // Première ligne : température
  webpage +=            "<input type='number' name='comptemp1' id='comptemp1' placeholder='";
  webpage +=            data.CompensationTemp;
  webpage +=            "' size=2 step='0.1' min='-10.00' max='+10.00'>";
//  webpage +=             CompensationTemp;
  webpage +=             "</h4></td><td><h4>";
  webpage +=            "<input type='number' name='comptemp2' id='comptemp2' placeholder='";
  webpage +=            data.CompensationTemp2;
  webpage +=            "' size=2 step='0.1' min='-10.00' max='+10.00'>";
//  webpage +=             CompensationTemp2;
  webpage +=             "</h4></td><td><h4>";
  webpage +=            "<input type='number' name='comptemp3' id='comptemp3' placeholder='";
  webpage +=            data.CompensationTemp3;
  webpage +=            "' size=2 step='0.1' min='-10.00' max='+10.00'>";
//  webpage +=             CompensationTemp3;
  webpage +=             "</h4></td></tr>";
   webpage +=           "<tr class='active'><td><h4>Hygrometrie</h4></td><td><h4>"; 
  webpage +=            "<input type='number' name='comphygro1' id='comphygro1' placeholder='";
  webpage +=            data.CompensationHumidity;
  webpage +=            "' size=2 step='0.1'>";
//  webpage +=             CompensationHumidity;
  webpage +=             "</h4></td><td><h4>";
  webpage +=            "<input type='number' name='comphygro2' id='comphygro2' placeholder='";
  webpage +=            data.CompensationHumidity2;
  webpage +=            "' size=2 step='0.1'>";
//  webpage +=             CompensationHumidity2;
  webpage +=             "</h4></td><td><h4>";
  webpage +=            "<input type='number' name='comphygro3' id='comphygro3' placeholder='";
  webpage +=            data.CompensationHumidity3;
  webpage +=            "' size=2 step='0.1'>";
//  webpage +=             CompensationHumidity3;
  webpage +=             "</h4></td></tr>"; 
  webpage +=           "<tr><td><h4>Luminosite</h4></td><td><h4>"; 
  webpage +=            "<input type='number' name='complight1' id='complight1' placeholder='";
  webpage +=            data.CompensationLight;
  webpage +=            "' size=2 step='0.1'>";
//  webpage +=             CompensationLight;
  webpage +=             "</h4></td><td><h4>";
  webpage +=            "<input type='number' name='complight2' id='complight2' placeholder='";
  webpage +=            data.CompensationLight2;
  webpage +=            "' size=2 step='0.1'>";
//  webpage +=             CompensationLight2;
  webpage +=             "</h4></td><td><h4>";
  webpage +=            "<input type='number' name='complight3' id='complight3' placeholder='";
  webpage +=            data.CompensationLight3;
  webpage +=            "' size=2 step='0.1'>";
//  webpage +=             CompensationLight3;
  webpage +=             "</h4></td></tr>"; 
  webpage +=           "<tr class='active'><td><h4>Pression</h4></td><td><h4>"; 
  webpage +=            "<input type='number' name='comppressure1' id='comppressure1' placeholder='";
  webpage +=            data.CompensationPressure;
  webpage +=            "' size=2 step='0.1'>";
//  webpage +=             CompensationPressure;
  webpage +=             "</h4></td><td><h4>";
  webpage +=            "<input type='number' name='comppressure2' id='comppressure2' placeholder='";
  webpage +=            data.CompensationPressure2;
  webpage +=            "' size=2 step='0.1'>";
//  webpage +=             CompensationPressure2;
  webpage +=             "</h4></td><td><h4>";
  webpage +=            "<input type='number' name='comppressure3' id='comppressure3' placeholder='";
  webpage +=            data.CompensationPressure3;
  webpage +=            "' size=2 step='0.1'>";
//  webpage +=             CompensationPressure3;
  webpage +=             "</h4></td></tr>"; 


  webpage +=           "<tr><td><h4>Time Zone</h4></td><td><h4>"; 
  webpage +=           "<input type='number' name='timezone' id='timezone' placeholder='";
  webpage +=           webserver.timezone;
  webpage +=           "' size=1 step='1'>";
  webpage +=             "</h4></td><td><h4>";

  webpage +=           "Heure d'ete (1=ete / 0=hivers)</h4></td><td><h4>"; 
  webpage +=           "<input type='number' name='heuredete' id='heuredete' placeholder='";
  webpage +=           webserver.summertime;
  webpage +=           "' size='1' step='1'>";
  webpage +=             "</h4></td><td><h4>";

 /* webpage +=     "<div class='checkbox'>";
  webpage +=     "<label>";
  webpage +=     "<input type='checkbox' value='test' name='heuredete' id='heuredete'";
  if (summertime == 1) {
    Serial.println("Check SummerTime");
    webpage += " checked";
  }
  webpage += ">";
  //webpage +=     "<span class='cr'><i class='cr-icon glyphicon glyphicon-ok'></i></span>";
  webpage +=     "Heure d'ete";
  webpage +=     "</label>";
  webpage +=     "</div>";*/

/*  webpage += "<h4>Standard Checkboxes</h4><hr />";
  webpage += "<div class='[ form-group ]'>";
  webpage += "<input type='checkbox' name='fancy-checkbox-default' id='fancy-checkbox-default' autocomplete='off' />";
  webpage += "<div class='[ btn-group ]'>";
  webpage += "<label for='fancy-checkbox-default' class='[ btn btn-default ]'>";
  webpage += "<span class='[ glyphicon glyphicon-ok ]'></span>";
  webpage += "<span> </span>";
  webpage += "</label>";
  webpage += "<label for='fancy-checkbox-default' class='[ btn btn-default active ]'>";
  webpage += "Heure d'ete";
  webpage += "</label>";
  webpage += "</div>";
  webpage += "</div>";*/


  /*
  webpage +=           "Heure d'ete : ";
 
  if (summertime == 1) {
    Serial.println("Check SummerTime");
    webpage += " (Oui) ";
  }
  
  webpage += "<div class='btn-group' role='group' aria-label='...'>";
  webpage += "<button type='button' class='btn btn-default name='heuredeteOn' id='heuredeteOn' ";
  
  Serial.print("SummerTime : ");
  Serial.println(summertime);
  Serial.flush();
  if (summertime == 1) {
    Serial.println("Check SummerTime");
    webpage += "active";
  }

  webpage += "'>Oui</button>";
  webpage += "<button type='button' class='btn btn-default name='heuredeteOff' id='heuredeteOff' ";
  
  if (summertime != 1) {
    Serial.println("UnCheck SummerTime");
    webpage += "active";
  }

  webpage +=   "'>Non</button>";
  webpage +=   "</div>";
  
  webpage +=           "<input type='checkbox' name='heuredete' id='heuredete' value='heuredete'";
  Serial.print("SummerTime : ");
  Serial.println(summertime);
  Serial.flush();
  if (summertime == 1) {
    Serial.println("Check SummerTime");
    webpage += " checked";
  }
  webpage +=           "> Heure d'ete";*/

  webpage +=           "<tr><td><h4>SSID</h4></td><td><h4>"; 
  webpage +=           "<input type='text' name='wifissid' id='wifissid' placeholder='";
  webpage +=           webserver.wifissidconf;
  webpage +=           "' size=20 step='1'>";
  webpage +=             "</h4></td><td><h4>";

  webpage +=           "Passwod</h4></td><td><h4>"; 
  webpage +=           "<input type='text' name='wifipwd' id='wifipwd' placeholder='";
  webpage +=           webserver.wifipwdconf;
  webpage +=           "' size='20' step='1' >";
  webpage +=             "</h4></td><td><h4>";

  
  webpage +=             "</h4></td></tr>"; 
 
  webpage +=       "</tbody></table></div>";


 /* webpage += "</li></ul></h1>";
  webpage += "<ul><li><h3>Compensation de Temperature</h3>";
  webpage += "<input type='number' name='comptemp1' id='comptemp1' placeholder='";
  webpage += CompensationTemp;
  webpage += "' size=2 step='0.1' min='-10.00' max='+10.00'> - ";
  webpage += "<input type='number' name='comptemp2' id='comptemp2' placeholder='";
  webpage += CompensationTemp2;
  webpage += "' size=2 step='0.1'> - ";
  webpage += "<input type='number' name='comptemp3' id='comptemp3' placeholder='";
  webpage += CompensationTemp3;
  webpage += "' size=2 step='0.1'>";
  webpage += "</li></ul>";

  webpage += "<ul><li><h3>Compensation d'Hygrometrie</h3>";
  webpage += "<input type='number' name='comphygro1' id='comphygro1' placeholder='";
  webpage += CompensationHumidity;
  webpage += "' size=2 step='0.1'> - ";
  webpage += "<input type='number' name='comphygro2' id='comphygro2' placeholder='";
  webpage += CompensationHumidity2;
  webpage += "' size=2 step='0.1'> - ";
  webpage += "<input type='number' name='comphygro3' id='comphygro3' placeholder='";
  webpage += CompensationHumidity3;
  webpage += "' size=2 step='0.1'>";
  webpage += "</li></ul>";

  webpage += "<ul><li><h3>Compensation Luminosite</h3>";
  webpage += "<input type='number' name='complight1' id='complight1' placeholder='";
  webpage += CompensationLight;
  webpage += "' size=2 step='0.1'> - ";
  webpage += "<input type='number' name='complight2' id='complight2' placeholder='";
  webpage += CompensationLight2;
  webpage += "' size=2 step='0.1'> - ";
  webpage += "<input type='number' name='complight3' id='complight3' placeholder='";
  webpage += CompensationLight3;
  webpage += "' size=2 step='0.1'>";
  webpage += "</li></ul>";

  webpage += "<ul><li><h3>Compensation de Pression</h3>";
  webpage += "<input type='number' name='comppressure1' id='comppressure1' placeholder='";
  webpage += CompensationPressure;
  webpage += "' size=2 step='0.1'> - ";
  webpage += "<input type='number' name='comppressure2' id='comppressure2' placeholder='";
  webpage += CompensationPressure2;
  webpage += "' size=2 step='0.1'> - ";
  webpage += "<input type='number' name='comppressure3' id='comppressure3' placeholder='";
  webpage += CompensationPressure3;
  webpage += "' size=2 step='0.1'>";
  webpage += "</li></ul>";*/



 /* webpage += "<div class='py-5'>";
  webpage += "<div class='container'>";
  webpage += "<div class='row'>";
  webpage += "<div class='col-sm-2'><h4>Mot de passe</h4></div>";
  webpage += "<div class='col-sm-3'>";
  webpage += "<input type='Maj pwd' name='psw' id='psw'>";
  webpage += "</div></div></div>";*/

  webpage += "<div class='py-5'>";
  webpage += "<div class='container'>";
  webpage += "<div class='row'>";
  webpage += "<div class='col-sm-2'><h4>Sonde Numero</h4></div>";
  webpage += "<div class='col-sm-3'>";
  webpage += "<input type='number' name='sondenumber' id='sondenumber' placeholder='";
  webpage += data.sondeNumber;
  webpage += "' size='2' step='1' min='0' max='99'>";
  webpage += "</div></div></div>";  
/*  webpage += "<h3>Time Zone</h3>";
  webpage += "<input type='number' name='timezone' id='timezone' placeholder='";
  webpage += timezone;
  webpage += "' size=2 step='0.1'>";
  webpage += "</li></ul>";

  webpage += "<ul><li>";
  webpage += "<input type='checkbox' name='heuredete' value='heuredete'";
  if (summertime == 1) webpage += " checked";
  webpage += "> Heure d'ete<br>";
  webpage += "</li></ul>";

  webpage += "<ul><li><h3>Mot de passe</h3>";
  webpage += "<input type='password' name='psw' id='psw'>";
  webpage += "</li></ul>";*/
  
  webpage += "</form>";
  webpage += "</body>";
  webpage += "</html>";
  
  server.send(200, "text/html", webpage); // Send a response to the client asking for input
  
  Serial.println("Affichage page web ---------------------");
  Serial.print("server.args() : ");
  Serial.println(server.args());

  if (server.args() > 0 ) { // Arguments were received

     int EEaddress = 0;
     int EEaddressTmp = 0;
     int integer_variable = 0;
     float floatingpoint_variable = 0;
     boolean CompensationTempSaisie, CompensationTempSaisie2, CompensationTempSaisie3;
     boolean CompensationHumiditySaisie, CompensationHumiditySaisie2, CompensationHumiditySaisie3;
     boolean CompensationLightSaisie, CompensationLightSaisie2, CompensationLightSaisie3;
     boolean CompensationPressureSaisie, CompensationPressureSaisie2, CompensationPressureSaisie3;
     boolean TimeZoneSaisie, SummerTimeSaisie, sondeNumberSaisie;

     CompensationTempSaisie = CompensationTempSaisie2 = CompensationTempSaisie3 = false;
     CompensationHumiditySaisie = CompensationHumiditySaisie2 = CompensationHumiditySaisie3 = false;
     CompensationLightSaisie = CompensationLightSaisie2 = CompensationLightSaisie3 = false;
     CompensationPressureSaisie = CompensationPressureSaisie2 = CompensationPressureSaisie3 = false;
     TimeZoneSaisie = SummerTimeSaisie = false;

    for ( uint8_t i = 0; i < server.args(); i++ ) {
      Serial.print("server.argName : ");
      Serial.print(server.argName(i)); // Display the argument
      Serial.print("   -   ");
      Argument_Name = server.argName(i);
      if (server.argName(i) == "name_input") {
        Serial.print(" Input received was: ");
        Serial.println(server.arg(i));
        Clients_Response1 = server.arg(i);
        // e.g. range_maximum = server.arg(i).toInt();   // use string.toInt()   if you wanted to convert the input to an integer number
        // e.g. range_maximum = server.arg(i).toFloat(); // use string.toFloat() if you wanted to convert the input to a floating point number
      }
      if (server.argName(i) == "address_input") {
        Serial.print(" Input received was: ");
        Serial.println(server.arg(i));
        Clients_Response2 = server.arg(i);
        // e.g. range_maximum = server.arg(i).toInt();   // use string.toInt()   if you wanted to convert the input to an integer number
        // e.g. range_maximum = server.arg(i).toFloat(); // use string.toFloat() if you wanted to convert the input to a floating point number
      }
      
      if (server.argName(i) == "comptemp1") {
        Serial.print(" Input received was: ");
        Serial.print(server.argName(i));
        Serial.print(" - valeur : ");
        Serial.print(server.arg(i));
        Serial.println(" -------------------------------------------");
 //       Clients_Response1 = server.arg(i);
        // e.g. range_maximum = server.arg(i).toInt();   // use string.toInt()   if you wanted to convert the input to an integer number
        // e.g. range_maximum = server.arg(i).toFloat(); // use string.toFloat() if you wanted to convert the input to a floating point number

        if (server.arg(i) != "") {
          data.CompensationTemp = server.arg(i).toFloat();
          CompensationTempSaisie = true;
        }
      }
      
      if (server.argName(i) == "comptemp2") {
        Serial.print(" Input received was: ");
        Serial.print(server.argName(i));
        Serial.print(" - valeur : ");
        Serial.print(server.arg(i));
        Serial.println(" -------------------------------------------");
 //       Clients_Response1 = server.arg(i);
        // e.g. range_maximum = server.arg(i).toInt();   // use string.toInt()   if you wanted to convert the input to an integer number
        // e.g. range_maximum = server.arg(i).toFloat(); // use string.toFloat() if you wanted to convert the input to a floating point number
        if (server.arg(i) != "") {
          data.CompensationTemp2 = server.arg(i).toFloat();
          CompensationTempSaisie2 = true;
        }
      }
      
      if (server.argName(i) == "comptemp3") {
        Serial.print(" Input received was: ");
        Serial.print(server.argName(i));
        Serial.print(" - valeur : ");
        Serial.print(server.arg(i));
        Serial.println(" -------------------------------------------");
 //       Clients_Response1 = server.arg(i);
        // e.g. range_maximum = server.arg(i).toInt();   // use string.toInt()   if you wanted to convert the input to an integer number
        // e.g. range_maximum = server.arg(i).toFloat(); // use string.toFloat() if you wanted to convert the input to a floating point number
        if (server.arg(i) != "") {
          data.CompensationTemp3 = server.arg(i).toFloat();
          CompensationTempSaisie3 = true;
        } 
      }
      
      if (server.argName(i) == "comphygro1") {
        Serial.print(" Input received was: ");
        Serial.print(server.argName(i));
        Serial.print(" - valeur : ");
        Serial.print(server.arg(i));
        Serial.println(" -------------------------------------------");
 //       Clients_Response1 = server.arg(i);
        // e.g. range_maximum = server.arg(i).toInt();   // use string.toInt()   if you wanted to convert the input to an integer number
        // e.g. range_maximum = server.arg(i).toFloat(); // use string.toFloat() if you wanted to convert the input to a floating point number
        if (server.arg(i) != "") {
          data.CompensationHumidity = server.arg(i).toFloat();
          CompensationHumiditySaisie = true;
        }       
      }
      
      if (server.argName(i) == "comphygro2") {
        Serial.print(" Input received was: ");
        Serial.print(server.argName(i));
        Serial.print(" - valeur : ");
        Serial.print(server.arg(i));
        Serial.println(" -------------------------------------------");
 //       Clients_Response1 = server.arg(i);
        // e.g. range_maximum = server.arg(i).toInt();   // use string.toInt()   if you wanted to convert the input to an integer number
        // e.g. range_maximum = server.arg(i).toFloat(); // use string.toFloat() if you wanted to convert the input to a floating point number
        if (server.arg(i) != "") {
          data.CompensationHumidity2 = server.arg(i).toFloat();
          CompensationHumiditySaisie2 = true;
        }       
      }
      
      if (server.argName(i) == "comphygro3") {
        Serial.print(" Input received was: ");
        Serial.print(server.argName(i));
        Serial.print(" - valeur : ");
        Serial.print(server.arg(i));
        Serial.println(" -------------------------------------------");
 //       Clients_Response1 = server.arg(i);
        // e.g. range_maximum = server.arg(i).toInt();   // use string.toInt()   if you wanted to convert the input to an integer number
        // e.g. range_maximum = server.arg(i).toFloat(); // use string.toFloat() if you wanted to convert the input to a floating point number
        if (server.arg(i) != "") {
          data.CompensationHumidity3 = server.arg(i).toFloat();
          CompensationHumiditySaisie3 = true;
        }       
      }
      
      if (server.argName(i) == "complight1") {
        Serial.print(" Input received was: ");
        Serial.print(server.argName(i));
        Serial.print(" - valeur : ");
        Serial.print(server.arg(i));
        Serial.println(" -------------------------------------------");
 //       Clients_Response1 = server.arg(i);
        // e.g. range_maximum = server.arg(i).toInt();   // use string.toInt()   if you wanted to convert the input to an integer number
        // e.g. range_maximum = server.arg(i).toFloat(); // use string.toFloat() if you wanted to convert the input to a floating point number
        if (server.arg(i) != "") {
          data.CompensationLight = server.arg(i).toFloat();
          CompensationLightSaisie = true;
        }       
      }
      
      if (server.argName(i) == "complight2") {
        Serial.print(" Input received was: ");
        Serial.print(server.argName(i));
        Serial.print(" - valeur : ");
        Serial.print(server.arg(i));
        Serial.println(" -------------------------------------------");
 //       Clients_Response1 = server.arg(i);
        // e.g. range_maximum = server.arg(i).toInt();   // use string.toInt()   if you wanted to convert the input to an integer number
        // e.g. range_maximum = server.arg(i).toFloat(); // use string.toFloat() if you wanted to convert the input to a floating point number
        if (server.arg(i) != "") {
          data.CompensationLight2 = server.arg(i).toFloat();
          CompensationLightSaisie2 = true;
        }       
      }
      
      if (server.argName(i) == "complight3") {
        Serial.print(" Input received was: ");
        Serial.print(server.argName(i));
        Serial.print(" - valeur : ");
        Serial.print(server.arg(i));
        Serial.println(" -------------------------------------------");
 //       Clients_Response1 = server.arg(i);
        // e.g. range_maximum = server.arg(i).toInt();   // use string.toInt()   if you wanted to convert the input to an integer number
        // e.g. range_maximum = server.arg(i).toFloat(); // use string.toFloat() if you wanted to convert the input to a floating point number
        if (server.arg(i) != "") {
          data.CompensationLight3 = server.arg(i).toFloat();
          CompensationLightSaisie3 = true;
        }   
      }
      
      if (server.argName(i) == "comppressure1") {
        Serial.print(" Input received was: ");
        Serial.print(server.argName(i));
        Serial.print(" - valeur : ");
        Serial.print(server.arg(i));
        Serial.println(" -------------------------------------------");
 //       Clients_Response1 = server.arg(i);
        // e.g. range_maximum = server.arg(i).toInt();   // use string.toInt()   if you wanted to convert the input to an integer number
        // e.g. range_maximum = server.arg(i).toFloat(); // use string.toFloat() if you wanted to convert the input to a floating point number
        if (server.arg(i) != "") {
          data.CompensationPressure = server.arg(i).toFloat();
          CompensationPressureSaisie = true;
        }   
      }
      
      if (server.argName(i) == "comppressure2") {
        Serial.print(" Input received was: ");
        Serial.print(server.argName(i));
        Serial.print(" - valeur : ");
        Serial.print(server.arg(i));
        Serial.println(" -------------------------------------------");
 //       Clients_Response1 = server.arg(i);
        // e.g. range_maximum = server.arg(i).toInt();   // use string.toInt()   if you wanted to convert the input to an integer number
        // e.g. range_maximum = server.arg(i).toFloat(); // use string.toFloat() if you wanted to convert the input to a floating point number
        if (server.arg(i) != "") {
          data.CompensationPressure2 = server.arg(i).toFloat();
          CompensationPressureSaisie2 = true;
        }   
      }
      
      if (server.argName(i) == "comppressure3") {
        Serial.print(" Input received was: ");
        Serial.print(server.argName(i));
        Serial.print(" - valeur : ");
        Serial.print(server.arg(i));
        Serial.println(" -------------------------------------------");
 //       Clients_Response1 = server.arg(i);
        // e.g. range_maximum = server.arg(i).toInt();   // use string.toInt()   if you wanted to convert the input to an integer number
        // e.g. range_maximum = server.arg(i).toFloat(); // use string.toFloat() if you wanted to convert the input to a floating point number
        if (server.arg(i) != "") {
          data.CompensationPressure3 = server.arg(i).toFloat();
          CompensationPressureSaisie3 = true;
        }   
      }

      if (server.argName(i) == "timezone") {
        Serial.print(" Input received was: ");
        Serial.print(server.argName(i));
        Serial.print(" - valeur : ");
        Serial.print(server.arg(i));
        Serial.println(" -------------------------------------------");
 //       Clients_Response1 = server.arg(i);
        // e.g. range_maximum = server.arg(i).toInt();   // use string.toInt()   if you wanted to convert the input to an integer number
        // e.g. range_maximum = server.arg(i).toFloat(); // use string.toFloat() if you wanted to convert the input to a floating point number
        if (server.arg(i) != "") {
          webserver.timezone = server.arg(i).toInt();
          TimeZoneSaisie = true;
        }         
      }

      if (server.argName(i) == "heuredete") {
        Serial.print(" Input received was: ");
        Serial.print(server.argName(i));
        Serial.print(" - valeur : ");
        Serial.print(server.arg(i));
        Serial.println(" -------------------------------------------");
        // e.g. range_maximum = server.arg(i).toInt();   // use string.toInt()   if you wanted to convert the input to an integer number
        // e.g. range_maximum = server.arg(i).toFloat(); // use string.toFloat() if you wanted to convert the input to a floating point number
/*        if (server.arg(i) == "1") {        
          summertime = 1;
          SummerTimeSaisie = true;
        }    
        else if (server.arg(i) == "0") {        
          summertime = 0;     
          SummerTimeSaisie = true;
        }*/
        if (server.arg(i) != "") {
          webserver.summertime = server.arg(i).toInt();
          SummerTimeSaisie = true;
        }
      }

      if (server.argName(i) == "psw") {
        Serial.print(" Input received was: ");
        Serial.println(server.arg(i));
        String Password = server.arg(i);
        if (Password == PASSWORD_WEB) SauveParam = true;
        // e.g. range_maximum = server.arg(i).toInt();   // use string.toInt()   if you wanted to convert the input to an integer number
        // e.g. range_maximum = server.arg(i).toFloat(); // use string.toFloat() if you wanted to convert the input to a floating point number
      }

      if (server.argName(i) == "sondenumber") {
        Serial.print(" Input received was: ");
        Serial.print(server.argName(i));
        Serial.print(" - valeur : ");
        Serial.print(server.arg(i));
        Serial.println(" -------------------------------------------");
        // e.g. range_maximum = server.arg(i).toInt();   // use string.toInt()   if you wanted to convert the input to an integer number
        // e.g. range_maximum = server.arg(i).toFloat(); // use string.toFloat() if you wanted to convert the input to a floating point number
/*        if (server.arg(i) == "1") {        
          summertime = 1;
          SummerTimeSaisie = true;
        }    
        else if (server.arg(i) == "0") {        
          summertime = 0;     
          SummerTimeSaisie = true;
        }*/
        if (server.arg(i) != "") {
          data.sondeNumber = server.arg(i).toInt();
					if (data.sondeNumber < 0)  data.sondeNumber = 0;
					if (data.sondeNumber > 99) data.sondeNumber = 99;
					itoa(data.sondeNumber, data.CapteurID, 10);
          sondeNumberSaisie = true;
        }
      }      
    }

    if (SauveParam) {
      Serial.println("Sauvegarde des paramettres ---------------------------------");

      EEPROM.begin(300);  //EEPROM.begin(Size)
  
/*      integer_variable = 12345;
      EEaddress = data.EEPROMAnythingWrite(1, reinterpret_cast<char*>(&integer_variable), sizeof(integer_variable));*/

      if (CompensationTempSaisie) {
        floatingpoint_variable = data.CompensationTemp;
//        EEaddressTmp = EEaddress + (sizeof(floatingpoint_variable) * 0);
//        EEaddressTmp = data.EEPROMAnythingWrite(EEaddressTmp, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));
        EEaddress = EEaddress + sizeof(int) + (sizeof(float) * 2) + (sizeof(float) * 0) + (sizeof(int) * 0);
        EEPROM.put(EEaddress, floatingpoint_variable);
        Serial.print("Sauvegarde compensation temp : ");
        Serial.println(data.CompensationTemp);
      }

      if (CompensationTempSaisie2) {
        floatingpoint_variable = data.CompensationTemp2;
 /*       EEaddressTmp = EEaddress + (sizeof(floatingpoint_variable) * 1);
        EEaddressTmp = data.EEPROMAnythingWrite(EEaddressTmp, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));*/
        EEaddress = EEaddress + sizeof(int) + (sizeof(float) * 2) + (sizeof(float) * 1) + (sizeof(int) * 0);
        EEPROM.put(EEaddress, floatingpoint_variable);
        Serial.print("Sauvegarde compensation temp 2 : ");
        Serial.println(data.CompensationTemp2);
      }

      if (CompensationTempSaisie3) {
        floatingpoint_variable = data.CompensationTemp3;
 //       EEaddressTmp = EEaddress + (sizeof(floatingpoint_variable) * 2);
 //       EEaddressTmp = data.EEPROMAnythingWrite(EEaddressTmp, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));
        EEaddress = EEaddress + sizeof(int) + (sizeof(float) * 2) + (sizeof(float) * 2) + (sizeof(int) * 0);
        EEPROM.put(EEaddress, floatingpoint_variable);
        Serial.print("Sauvegarde compensation temp 3 : ");
        Serial.println(data.CompensationTemp2);
      }

       if (CompensationHumiditySaisie) {
        floatingpoint_variable = data.CompensationHumidity;
//        EEaddressTmp = EEaddress + (sizeof(floatingpoint_variable) * 3);
//        EEaddressTmp = data.EEPROMAnythingWrite(EEaddressTmp, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));
        EEaddress = EEaddress + sizeof(int) + (sizeof(float) * 2) + (sizeof(float) * 3) + (sizeof(int) * 0);
        EEPROM.put(EEaddress, floatingpoint_variable);
        Serial.print("Sauvegarde compensation Humidite : ");
        Serial.println(data.CompensationHumidity);
      }

      if (CompensationHumiditySaisie2) {
        floatingpoint_variable = data.CompensationHumidity2;
//        EEaddressTmp = EEaddress + (sizeof(floatingpoint_variable) * 4);
//        EEaddressTmp = data.EEPROMAnythingWrite(EEaddressTmp, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));
        EEaddress = EEaddress + sizeof(int) + (sizeof(float) * 2) + (sizeof(float) * 4) + (sizeof(int) * 0);
        EEPROM.put(EEaddress, floatingpoint_variable);
        Serial.print("Sauvegarde compensation Humidite 2 : ");
        Serial.println(data.CompensationHumidity2);
      }

      if (CompensationHumiditySaisie3) {
        floatingpoint_variable = data.CompensationHumidity3;
//        EEaddressTmp = EEaddress + (sizeof(floatingpoint_variable) * 5);
//        EEaddressTmp = data.EEPROMAnythingWrite(EEaddressTmp, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));
        EEaddress = EEaddress + sizeof(int) + (sizeof(float) * 2) + (sizeof(float) * 5) + (sizeof(int) * 0);
        EEPROM.put(EEaddress, floatingpoint_variable);
        Serial.print("Sauvegarde compensation Humidite 3 : ");
        Serial.println(data.CompensationHumidity3);
      }

      if (CompensationLightSaisie) {
        floatingpoint_variable = data.CompensationLight;
//        EEaddressTmp = EEaddress + (sizeof(floatingpoint_variable) * 6);
//        EEaddressTmp = data.EEPROMAnythingWrite(EEaddressTmp, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));
        EEaddress = EEaddress + sizeof(int) + (sizeof(float) * 2) + (sizeof(float) * 6) + (sizeof(int) * 0);
        EEPROM.put(EEaddress, floatingpoint_variable);
        Serial.print("Sauvegarde compensation Luminosite : ");
        Serial.println(data.CompensationLight);
      }

      if (CompensationLightSaisie2) {
        floatingpoint_variable = data.CompensationLight2;
//        EEaddressTmp = EEaddress + (sizeof(floatingpoint_variable) * 7);
//        EEaddressTmp = data.EEPROMAnythingWrite(EEaddressTmp, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));
        EEaddress = EEaddress + sizeof(int) + (sizeof(float) * 2) + (sizeof(float) * 7) + (sizeof(int) * 0);
        EEPROM.put(EEaddress, floatingpoint_variable);
        Serial.print("Sauvegarde compensation Luminosite 2 : ");
        Serial.println(data.CompensationLight2);
      }

      if (CompensationLightSaisie3) {
        floatingpoint_variable = data.CompensationLight3;
//        EEaddressTmp = EEaddress + (sizeof(floatingpoint_variable) * 8);
//        EEaddressTmp = data.EEPROMAnythingWrite(EEaddressTmp, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));
        EEaddress = EEaddress + sizeof(int) + (sizeof(float) * 2) + (sizeof(float) * 8) + (sizeof(int) * 0);
        EEPROM.put(EEaddress, floatingpoint_variable);
        Serial.print("Sauvegarde compensation Luminosite 3 : ");
        Serial.println(data.CompensationLight3);
      }

      if (CompensationPressureSaisie) {
        floatingpoint_variable = data.CompensationPressure;
//        EEaddressTmp = EEaddress + (sizeof(floatingpoint_variable) * 9);
//        EEaddressTmp = data.EEPROMAnythingWrite(EEaddressTmp, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));
        EEaddress = EEaddress + sizeof(int) + (sizeof(float) * 2) + (sizeof(float) * 9) + (sizeof(int) * 0);
        EEPROM.put(EEaddress, floatingpoint_variable);
        Serial.print("Sauvegarde compensation Pression : ");
        Serial.println(data.CompensationPressure);
      }

      if (CompensationPressureSaisie2) {
        floatingpoint_variable = data.CompensationPressure2;
//        EEaddressTmp = EEaddress + (sizeof(floatingpoint_variable) * 10);
//        EEaddressTmp = data.EEPROMAnythingWrite(EEaddressTmp, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));
        EEaddress = EEaddress + sizeof(int) + (sizeof(float) * 2) + (sizeof(float) * 10) + (sizeof(int) * 0);
        EEPROM.put(EEaddress, floatingpoint_variable);
        Serial.print("Sauvegarde compensation Pression 2 : ");
        Serial.println(data.CompensationPressure2);
      }

      if (CompensationPressureSaisie3) {
        floatingpoint_variable = data.CompensationPressure3;
//        EEaddressTmp = EEaddress + (sizeof(floatingpoint_variable) * 11);
//        EEaddressTmp = data.EEPROMAnythingWrite(EEaddressTmp, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));
        EEaddress = EEaddress + sizeof(int) + (sizeof(float) * 2) + (sizeof(float) * 11) + (sizeof(int) * 0);
        EEPROM.put(EEaddress, floatingpoint_variable);
        Serial.print("Sauvegarde compensation Pression 3 : ");
        Serial.println(data.CompensationPressure3);
      }

      if (TimeZoneSaisie) {
        integer_variable = webserver.timezone;
//        EEaddressTmp = EEaddress + (sizeof(floatingpoint_variable) * 12);
//        EEaddressTmp = data.EEPROMAnythingWrite(EEaddressTmp, reinterpret_cast<char*>(&integer_variable), sizeof(integer_variable));
        EEaddress = EEaddress + sizeof(int) + (sizeof(float) * 2) + (sizeof(float) * 12) + (sizeof(int) * 0);
        EEPROM.put(EEaddress, integer_variable);
        Serial.print("Sauvegarde timezone : ");
        Serial.println(webserver.timezone);
      }

      if (SummerTimeSaisie) {
        integer_variable = webserver.summertime;
//        EEaddressTmp = EEaddress + (sizeof(floatingpoint_variable) * 12) + sizeof(integer_variable);
//        EEaddressTmp = data.EEPROMAnythingWrite(EEaddressTmp, reinterpret_cast<char*>(&integer_variable), sizeof(integer_variable));
        EEaddress = EEaddress + sizeof(int) + (sizeof(float) * 2) + (sizeof(float) * 12) + (sizeof(int) * 1);
        EEPROM.put(EEaddress, integer_variable);
        Serial.print("Sauvegarde summertime : ");
        Serial.println(webserver.summertime);
      }

      if (sondeNumberSaisie) {
        integer_variable = data.sondeNumber;
//        EEaddressTmp = EEaddress + (sizeof(floatingpoint_variable) * 12) + sizeof(integer_variable*3);
//        EEaddressTmp = data.EEPROMAnythingWrite(EEaddressTmp, reinterpret_cast<char*>(&integer_variable), sizeof(integer_variable));
        EEaddress = EEaddress + sizeof(int) + (sizeof(float) * 2) + (sizeof(float) * 12) + (sizeof(int) * 3);
        EEPROM.put(EEaddress, integer_variable);
        Serial.print("Sauvegarde sondenumber : ");
        Serial.println(data.sondeNumber);
      }

      EEPROM.commit();    
      EEPROM.end();        
    }
  }
}

/********************************************/
void HandleResetParam() {
/********************************************/
  
  String webpage;

  webpage = "<html lang='fr'><head><meta http-equiv='refresh' content='60' name='viewport' content='width=device-width, initial-scale=1'/>";
  webpage += "<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css'><script src='https://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js'></script><script src='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js'></script>";
  webpage += "<title>ESP8266 MQTT - Parametrage</title></head><body>";
  webpage += "<div class='container-fluid'>";
  webpage +=   "<div class='row'>";
  webpage +=     "<div class='col-md-8'>";
  webpage +=       "<h1>ESP8266 MQTT - Parametrage</h1>";

/*  webpage =  "<html lang=fr-FR><meta http-equiv='refresh' content='60'/>";
  webpage += "<head><title>ESP8266 MQTT - Projet Sonde</title>";
  webpage += "<style>";
  webpage += "body { background-color: #E6E6FA; font-family: Arial, Helvetica, Sans-Serif; Color: blue;}";
  webpage += "</style>";
  webpage += "</head>";
  webpage += "<body>";


  webpage += "<h1><br>ESP8266 MQTT - Parametrage</h1>";*/
  webpage += "<TD><h3>Nom &nbsp;: ";
  webpage += data.CapteurName;
  webpage += "<br>";
  webpage += data.CapteurList;
  webpage += "</h3>";
  #ifdef DATATEMP
  webpage += "Temperature &nbsp;: ";
  Serial.print("Temperature   : ");
  Serial.println(data.temperature);
  webpage += data.temperature;
  webpage += "&ordm;C - (";
  webpage += data.CompensationTemp;
  webpage += ")<br>";
  #endif
  #ifdef DATATEMP2
  webpage += "Temperature 2 &nbsp;: ";
  webpage += data.temperature2;
  webpage += "&ordm;C - (";
  webpage += data.CompensationTemp2;
  webpage += ")<br>";
  #endif
  #ifdef DATATEMP3
  webpage += "Temperature 3 &nbsp;: ";
  webpage += data.temperature3;
  webpage += "&ordm;C - (";
  webpage += data.CompensationTemp3;
  webpage += ")<br>";
  #endif
  #ifdef DATAHUMIDITY
  webpage += "Humidite &nbsp;: ";
  webpage += data.humidity;
  webpage += "% - (";
  webpage += data.CompensationHumidity;
  webpage += ")<br>";
  #endif
  #ifdef DATAHUMIDITY2
  webpage += "Humidite 2 &nbsp;: ";
  webpage += data.humidity2;
  webpage += "% - (";
  webpage += data.CompensationHumidity2;
  webpage += ")<br>";
  #endif  
  #ifdef DATAHUMIDITY3
  webpage += "Humidite 3 &nbsp;: ";
  webpage += data.humidity3;
  webpage += "% - (";
  webpage += data.CompensationHumidity3;
  webpage += ")<br>";
  #endif
  #ifdef DATAPRESSURE
  webpage += "Pression atmospherique &nbsp;: ";
  webpage += data.pressure;
  webpage += " hPa - (";
  webpage += data.CompensationPressure;
  webpage += ")<br>";
  #endif
  #ifdef DATAPRESSURE2
  webpage += "Pression atmospherique 2 &nbsp;: ";
  webpage += data.pressure2;
  webpage += " hPa - (";
  webpage += data.CompensationPressure2;
  webpage += ")<br>";
  #endif  
  #ifdef DATAPRESSURE3
  webpage += "Pression atmospherique 3 &nbsp;: ";
  webpage += data.pressure3;
  webpage += " hPa - (";
  webpage += data.CompensationPressure3;
  webpage += ")<br>";
  #endif
  #ifdef DATALIGHT
  webpage += "Lumi&egrave;re &nbsp;: ";
  webpage += data.lux;
  webpage += " lux - (";
  webpage += data.CompensationLight;
  webpage += ")<br>";
  #endif
  #ifdef DATALIGHT2
  webpage += "Lumi&egrave;re 2 &nbsp;: ";
  webpage += data.lux2;
  webpage += " lux - (";
  webpage += data.CompensationLight2;
  webpage += ")<br>";
  #endif
  #ifdef DATALIGHT3
  webpage += "Lumi&egrave;re 3 &nbsp;: ";
  webpage += data.lux3;
  webpage += " lux - (";
  webpage += data.CompensationLight3;
  webpage += ")<br>";
  #endif
  webpage += "Date et Heure : ";
  webpage += webserver.timemesure;
  webpage += "<br>";
   
  String IPaddress = WiFi.localIP().toString();
  webpage += "Adresse IP : ";
  webpage += IPaddress;
  webpage += "<br>";

//  webpage += "<br><p><a href='http://"+IPaddress+"'>          Retour</a></p>";
  webpage += "<a class='btn btn-info btn-mg' href='http://"+IPaddress+"'>Retour </a>";

  webpage += "<div class='py-5'>";
  webpage += "<div class='container'>";
  webpage += "<div class='row'>";
  webpage += "<div class='col-sm-2'><h4>Mot de passe</h4></div>";
  webpage += "<div class='col-sm-3'>";
  webpage += "<input type='Maj pwd' name='psw' id='psw'>";
  webpage += "</div></div></div>";

  webpage += "<form action='http://"+IPaddress+"/parametre' method='POST'>";
/*  webpage += "&nbsp;&nbsp;&nbsp;&nbsp;Please enter your Name:<input type='text' name='name_input'><BR>";
  webpage += "Please enter your Address:<input type='text' name='address_input'>&nbsp;";*/
  webpage += "<h4><input type='submit' value='SAUVEGARDE'></h4>"; // omit <input type='submit' value='Enter'> for just 'enter'

  webpage += "<form action='http://"+IPaddress+"/resetparam' method='POST'>";
  webpage += "<h4><input type='submit' value='RESET'></h4>"; // omit <input type='submit' value='Enter'> for just 'enter'


  webpage +=       "<div class='table-responsive'>";
  webpage +=       "<table class='table table-condensed'>";  // Tableau des relevés
  webpage +=         "<thead><tr><th><h4>Type</h4></th><th><h4>Capteur 1</h4></th><th><h4>Capteur 2</h4></th><th><h4>Capteur 3</h4></th></tr></thead>"; //Entête
  webpage +=         "<tbody>";  // Contenu du tableau
  webpage +=           "<tr><td><h4>Temp&eacute;rature</h4></td><td><h4>"; // Première ligne : température
  webpage +=            "<input type='number' name='comptemp1' id='comptemp1' placeholder='";
  webpage +=            data.CompensationTemp;
  webpage +=            "' size=2 step='0.1' min='-10.00' max='+10.00'>";
//  webpage +=             CompensationTemp;
  webpage +=             "</h4></td><td><h4>";
  webpage +=            "<input type='number' name='comptemp2' id='comptemp2' placeholder='";
  webpage +=            data.CompensationTemp2;
  webpage +=            "' size=2 step='0.1' min='-10.00' max='+10.00'>";
//  webpage +=             CompensationTemp2;
  webpage +=             "</h4></td><td><h4>";
  webpage +=            "<input type='number' name='comptemp3' id='comptemp3' placeholder='";
  webpage +=            data.CompensationTemp3;
  webpage +=            "' size=2 step='0.1' min='-10.00' max='+10.00'>";
//  webpage +=             CompensationTemp3;
  webpage +=             "</h4></td></tr>";
   webpage +=           "<tr class='active'><td><h4>Hygrometrie</h4></td><td><h4>"; 
  webpage +=            "<input type='number' name='comphygro1' id='comphygro1' placeholder='";
  webpage +=            data.CompensationHumidity;
  webpage +=            "' size=2 step='0.1'>";
//  webpage +=             CompensationHumidity;
  webpage +=             "</h4></td><td><h4>";
  webpage +=            "<input type='number' name='comphygro2' id='comphygro2' placeholder='";
  webpage +=            data.CompensationHumidity2;
  webpage +=            "' size=2 step='0.1'>";
//  webpage +=             CompensationHumidity2;
  webpage +=             "</h4></td><td><h4>";
  webpage +=            "<input type='number' name='comphygro3' id='comphygro3' placeholder='";
  webpage +=            data.CompensationHumidity3;
  webpage +=            "' size=2 step='0.1'>";
//  webpage +=             CompensationHumidity3;
  webpage +=             "</h4></td></tr>"; 
  webpage +=           "<tr><td><h4>Luminosite</h4></td><td><h4>"; 
  webpage +=            "<input type='number' name='complight1' id='complight1' placeholder='";
  webpage +=            data.CompensationLight;
  webpage +=            "' size=2 step='0.1'>";
//  webpage +=             CompensationLight;
  webpage +=             "</h4></td><td><h4>";
  webpage +=            "<input type='number' name='complight2' id='complight2' placeholder='";
  webpage +=            data.CompensationLight2;
  webpage +=            "' size=2 step='0.1'>";
//  webpage +=             CompensationLight2;
  webpage +=             "</h4></td><td><h4>";
  webpage +=            "<input type='number' name='complight3' id='complight3' placeholder='";
  webpage +=            data.CompensationLight3;
  webpage +=            "' size=2 step='0.1'>";
//  webpage +=             CompensationLight3;
  webpage +=             "</h4></td></tr>"; 
  webpage +=           "<tr class='active'><td><h4>Pression</h4></td><td><h4>"; 
  webpage +=            "<input type='number' name='comppressure1' id='comppressure1' placeholder='";
  webpage +=            data.CompensationPressure;
  webpage +=            "' size=2 step='0.1'>";
//  webpage +=             CompensationPressure;
  webpage +=             "</h4></td><td><h4>";
  webpage +=            "<input type='number' name='comppressure2' id='comppressure2' placeholder='";
  webpage +=            data.CompensationPressure2;
  webpage +=            "' size=2 step='0.1'>";
//  webpage +=             CompensationPressure2;
  webpage +=             "</h4></td><td><h4>";
  webpage +=            "<input type='number' name='comppressure3' id='comppressure3' placeholder='";
  webpage +=            data.CompensationPressure3;
  webpage +=            "' size=2 step='0.1'>";
//  webpage +=             CompensationPressure3;
  webpage +=             "</h4></td></tr>"; 


  webpage +=           "<tr><td><h4>Time Zone</h4></td><td><h4>"; 
  webpage +=           "<input type='number' name='timezone' id='timezone' placeholder='";
  webpage +=           webserver.timezone;
  webpage +=           "' size=1 step='1'>";
  webpage +=             "</h4></td><td><h4>";

  webpage +=           "Heure d'ete (1=ete / 0=hivers)</h4></td><td><h4>"; 
  webpage +=           "<input type='number' name='heuredete' id='heuredete' placeholder='";
  webpage +=           webserver.summertime;
  webpage +=           "' size='1' step='1'>";
  webpage +=             "</h4></td><td><h4>";

 /* webpage +=     "<div class='checkbox'>";
  webpage +=     "<label>";
  webpage +=     "<input type='checkbox' value='test' name='heuredete' id='heuredete'";
  if (summertime == 1) {
    Serial.println("Check SummerTime");
    webpage += " checked";
  }
  webpage += ">";
  //webpage +=     "<span class='cr'><i class='cr-icon glyphicon glyphicon-ok'></i></span>";
  webpage +=     "Heure d'ete";
  webpage +=     "</label>";
  webpage +=     "</div>";*/

/*  webpage += "<h4>Standard Checkboxes</h4><hr />";
  webpage += "<div class='[ form-group ]'>";
  webpage += "<input type='checkbox' name='fancy-checkbox-default' id='fancy-checkbox-default' autocomplete='off' />";
  webpage += "<div class='[ btn-group ]'>";
  webpage += "<label for='fancy-checkbox-default' class='[ btn btn-default ]'>";
  webpage += "<span class='[ glyphicon glyphicon-ok ]'></span>";
  webpage += "<span> </span>";
  webpage += "</label>";
  webpage += "<label for='fancy-checkbox-default' class='[ btn btn-default active ]'>";
  webpage += "Heure d'ete";
  webpage += "</label>";
  webpage += "</div>";
  webpage += "</div>";*/


  /*
  webpage +=           "Heure d'ete : ";
 
  if (summertime == 1) {
    Serial.println("Check SummerTime");
    webpage += " (Oui) ";
  }
  
  webpage += "<div class='btn-group' role='group' aria-label='...'>";
  webpage += "<button type='button' class='btn btn-default name='heuredeteOn' id='heuredeteOn' ";
  
  Serial.print("SummerTime : ");
  Serial.println(summertime);
  Serial.flush();
  if (summertime == 1) {
    Serial.println("Check SummerTime");
    webpage += "active";
  }

  webpage += "'>Oui</button>";
  webpage += "<button type='button' class='btn btn-default name='heuredeteOff' id='heuredeteOff' ";
  
  if (summertime != 1) {
    Serial.println("UnCheck SummerTime");
    webpage += "active";
  }

  webpage +=   "'>Non</button>";
  webpage +=   "</div>";
  
  webpage +=           "<input type='checkbox' name='heuredete' id='heuredete' value='heuredete'";
  Serial.print("SummerTime : ");
  Serial.println(summertime);
  Serial.flush();
  if (summertime == 1) {
    Serial.println("Check SummerTime");
    webpage += " checked";
  }
  webpage +=           "> Heure d'ete";*/

  webpage +=           "<tr><td><h4>SSID</h4></td><td><h4>"; 
  webpage +=           "<input type='text' name='wifissid' id='wifissid' placeholder='";
  webpage +=           webserver.wifissidconf;
  webpage +=           "' size=20 step='1'>";
  webpage +=             "</h4></td><td><h4>";

  webpage +=           "Passwod</h4></td><td><h4>"; 
  webpage +=           "<input type='text' name='wifipwd' id='wifipwd' placeholder='";
  webpage +=           webserver.wifipwdconf;
  webpage +=           "' size='20' step='1' >";
  webpage +=             "</h4></td><td><h4>";

  
  webpage +=             "</h4></td></tr>"; 
 
  webpage +=       "</tbody></table></div>";


 /* webpage += "</li></ul></h1>";
  webpage += "<ul><li><h3>Compensation de Temperature</h3>";
  webpage += "<input type='number' name='comptemp1' id='comptemp1' placeholder='";
  webpage += CompensationTemp;
  webpage += "' size=2 step='0.1' min='-10.00' max='+10.00'> - ";
  webpage += "<input type='number' name='comptemp2' id='comptemp2' placeholder='";
  webpage += CompensationTemp2;
  webpage += "' size=2 step='0.1'> - ";
  webpage += "<input type='number' name='comptemp3' id='comptemp3' placeholder='";
  webpage += CompensationTemp3;
  webpage += "' size=2 step='0.1'>";
  webpage += "</li></ul>";

  webpage += "<ul><li><h3>Compensation d'Hygrometrie</h3>";
  webpage += "<input type='number' name='comphygro1' id='comphygro1' placeholder='";
  webpage += CompensationHumidity;
  webpage += "' size=2 step='0.1'> - ";
  webpage += "<input type='number' name='comphygro2' id='comphygro2' placeholder='";
  webpage += CompensationHumidity2;
  webpage += "' size=2 step='0.1'> - ";
  webpage += "<input type='number' name='comphygro3' id='comphygro3' placeholder='";
  webpage += CompensationHumidity3;
  webpage += "' size=2 step='0.1'>";
  webpage += "</li></ul>";

  webpage += "<ul><li><h3>Compensation Luminosite</h3>";
  webpage += "<input type='number' name='complight1' id='complight1' placeholder='";
  webpage += CompensationLight;
  webpage += "' size=2 step='0.1'> - ";
  webpage += "<input type='number' name='complight2' id='complight2' placeholder='";
  webpage += CompensationLight2;
  webpage += "' size=2 step='0.1'> - ";
  webpage += "<input type='number' name='complight3' id='complight3' placeholder='";
  webpage += CompensationLight3;
  webpage += "' size=2 step='0.1'>";
  webpage += "</li></ul>";

  webpage += "<ul><li><h3>Compensation de Pression</h3>";
  webpage += "<input type='number' name='comppressure1' id='comppressure1' placeholder='";
  webpage += CompensationPressure;
  webpage += "' size=2 step='0.1'> - ";
  webpage += "<input type='number' name='comppressure2' id='comppressure2' placeholder='";
  webpage += CompensationPressure2;
  webpage += "' size=2 step='0.1'> - ";
  webpage += "<input type='number' name='comppressure3' id='comppressure3' placeholder='";
  webpage += CompensationPressure3;
  webpage += "' size=2 step='0.1'>";
  webpage += "</li></ul>";*/



 /* webpage += "<div class='py-5'>";
  webpage += "<div class='container'>";
  webpage += "<div class='row'>";
  webpage += "<div class='col-sm-2'><h4>Mot de passe</h4></div>";
  webpage += "<div class='col-sm-3'>";
  webpage += "<input type='Maj pwd' name='psw' id='psw'>";
  webpage += "</div></div></div>";*/

  webpage += "<div class='py-5'>";
  webpage += "<div class='container'>";
  webpage += "<div class='row'>";
  webpage += "<div class='col-sm-2'><h4>Sonde Numero</h4></div>";
  webpage += "<div class='col-sm-3'>";
  webpage += "<input type='number' name='sondenumber' id='sondenumber' placeholder='";
  webpage += data.sondeNumber;
  webpage += "' size='2' step='1' min='0' max='99'>";
  webpage += "</div></div></div>";  
/*  webpage += "<h3>Time Zone</h3>";
  webpage += "<input type='number' name='timezone' id='timezone' placeholder='";
  webpage += timezone;
  webpage += "' size=2 step='0.1'>";
  webpage += "</li></ul>";

  webpage += "<ul><li>";
  webpage += "<input type='checkbox' name='heuredete' value='heuredete'";
  if (summertime == 1) webpage += " checked";
  webpage += "> Heure d'ete<br>";
  webpage += "</li></ul>";

  webpage += "<ul><li><h3>Mot de passe</h3>";
  webpage += "<input type='password' name='psw' id='psw'>";
  webpage += "</li></ul>";*/
  
  webpage += "</form>";
  webpage += "</body>";
  webpage += "</html>";
  
  server.send(200, "text/html", webpage); // Send a response to the client asking for input
  
  Serial.println("Affichage page web ---------------------");
  Serial.print("server.args() : ");
  Serial.println(server.args());

	data.initEeproom();

}

/********************************************/
void ShowClientResponse() {
/********************************************/
  String webpage;
  webpage =  "<html>";
   webpage += "<head><title>ESP8266 Input Example</title>";
    webpage += "<style>";
     webpage += "body { background-color: #E6E6FA; font-family: Arial, Helvetica, Sans-Serif; Color: blue;}";
    webpage += "</style>";
   webpage += "</head>";
   webpage += "<body>";
    webpage += "<h1><br>ESP8266 Server - This was what the client sent</h1>";
    webpage += "<p>Name received was: " + Clients_Response1 + "</p>";
    webpage += "<p>Address received was: " + Clients_Response2 + "</p>";
   webpage += "</body>";
  webpage += "</html>";
  server.send(200, "text/html", webpage); // Send a response to the client asking for input
}

/********************************************/
void HandleReboot(){ 
/********************************************/
  ESP.restart();
}


