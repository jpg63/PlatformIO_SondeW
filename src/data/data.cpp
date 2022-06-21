/* Data -- 
 *
 * Copyright 2020 Jean-philippe GOI
 * 
 */

/*********************************************************************************/
/*                                                                               */
/*                               Data                                            */
/*                                                                               */
/*  version    Date        Description                                           */
/*    1.0      28/12/20                                                          */
/*    1.0.1    10/01/21    Correction capteurID, Ip serveur mqtt                 */
/*    1.0.2    21/01/21    Modif gestion eeprom                                  */
/*                                                                               */
/*																																							 */
/*********************************************************************************/

#include <data.h>
#include <Arduino.h>

#include "settings.h"
#include "webserver.h"

#include <EEPROM.h>

#include <ErrorManager.h>

extern ErrorManager errormanager;

Data data;


// https://github.com/G6EJD/Using-ESP8266-EEPROM/blob/master/ESP8266_Reading_and_Writing_EEPROM.ino


void Data::init(void) {
/*-------------------------------------------------*/
/* Lecteur paramettre dans l'EEPROM                */
/*-------------------------------------------------*/
 
  EEPROM.begin(300);  //EEPROM.begin(Size)
	delay(100);
  int EEaddress = 0;
  int integer_variable = 0;
  float floatingpoint_variable = 0;
//	String string_variable = "XX.XX";

    // Integer read from EEPROM
//  EEaddress = EEPROMAnythingRead(1, reinterpret_cast<char*>(&integer_variable), sizeof(integer_variable));

//  EEPROM.get(EEaddress, integer_variable);
/*	for(int i=0; i<20; i++) {
	  if (integer_variable != 12345) 
		 {
			EEPROM.end();
			EEPROM.begin(300);  //EEPROM.begin(Size)
			delay(100);
			EEPROM.get(EEaddress, integer_variable);
			
			Serial.print("Erreur EEPROM - Tag Eeprom : ");
			Serial.println(integer_variable);
		 }
		else {
			break;
		}
	}*/

	EEaddress = EEaddress + sizeof(integer_variable);

#ifdef RESETCOMP
  integer_variable = 123456;
#endif

	Serial.print("EEPROM Lecture - Tag Eeprom : ");
	Serial.println(integer_variable);

//	EEaddress = EEPROMAnythingRead(EEaddress, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));

	EEPROM.get(EEaddress,	floatingpoint_variable);
  EEaddress = EEaddress + sizeof(floatingpoint_variable);

	Serial.print("EEPROM Lecture - Tag Float Eeprom : ");
	float tmpfloatpoint = floatingpoint_variable;
	Serial.print(tmpfloatpoint,2);

	EEPROM.get(EEaddress,	floatingpoint_variable);
  EEaddress = EEaddress + (sizeof(floatingpoint_variable)*2);

	Serial.print("EEPROM Lecture - Version de l'Eeprom : ");
	Serial.print(floatingpoint_variable,2);
	Serial.print(" - Version Code : ");
	Serial.println(VERSIONPARAM);
	VersionParam = floatingpoint_variable;
	char buffer1[30];
	char buffer2[30];
	dtostrf(VersionParam,5,2,buffer1);
	dtostrf(VERSIONPARAM,5,2,buffer2);
	Serial.println(buffer1);
	Serial.println(buffer2);	
  EEPROM.end();

  if ((integer_variable == 12345) && (tmpfloatpoint == 123.45) && (strcmp(buffer1, buffer2) == 0)) 
	{
		readEeproom();
	}
  else if ((integer_variable != 12345) && (tmpfloatpoint == 123.45) && (strcmp(buffer1, buffer2) == 0)) 
	{
		readEeproom();
	}
  else if ((integer_variable == 12345) && (tmpfloatpoint != 123.45) && (strcmp(buffer1, buffer2) == 0)) 
	{
		readEeproom();
	}
  else 
  {
		initEeproom();
  }
}


/*********************************************/
/* readEeproom                               */
/*********************************************/

void Data::readEeproom(void)
{
//  EEPROM.begin(100);  //EEPROM.begin(Size)
  EEPROM.begin(300);  //EEPROM.begin(Size)
  int EEaddress = 0;
  int integer_variable = 0;
  float floatingpoint_variable = 0;

    // Integer read from EEPROM
//  EEaddress = EEPROMAnythingRead(1, reinterpret_cast<char*>(&integer_variable), sizeof(integer_variable));

  EEPROM.get(EEaddress, integer_variable);
	EEaddress = EEaddress + sizeof(integer_variable);

	Serial.print("EEPROM Lecture - Tag Eeprom : ");
	Serial.println(integer_variable);
	
//	EEaddress = EEPROMAnythingRead(EEaddress, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));

  EEPROM.get(EEaddress, floatingpoint_variable);
  EEaddress = EEaddress + sizeof(floatingpoint_variable);
	Serial.print("EEPROM Lecture - Version de l'Eeprom : ");
	Serial.print(floatingpoint_variable,2);
	
	Serial.print(" - Version Data : ");
	Serial.println(VERSIONPARAM);
	VersionParam = floatingpoint_variable;  //floatingpoint_variable;
	
//	EEaddress = EEPROMAnythingRead(EEaddress, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));
  EEPROM.get(EEaddress, floatingpoint_variable);
  EEaddress = EEaddress + sizeof(floatingpoint_variable);
	Serial.print("EEPROM Lecture - Compensation Temperature   : ");
	Serial.println(floatingpoint_variable,2);
	CompensationTemp = floatingpoint_variable;

//	EEaddress = EEPROMAnythingRead(EEaddress, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));
  EEPROM.get(EEaddress, floatingpoint_variable);
  EEaddress = EEaddress + sizeof(floatingpoint_variable);
	Serial.print("EEPROM Lecture - Compensation Temperature 2 : ");
	Serial.println(floatingpoint_variable,2);
	CompensationTemp2 = floatingpoint_variable;

//	EEaddress = EEPROMAnythingRead(EEaddress, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));
  EEPROM.get(EEaddress, floatingpoint_variable);
  EEaddress = EEaddress + sizeof(floatingpoint_variable);
	Serial.print("EEPROM Lecture - Compensation Temperature 3 : ");
	Serial.println(floatingpoint_variable,2);
	CompensationTemp3 = floatingpoint_variable;
 
//	EEaddress = EEPROMAnythingRead(EEaddress, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));
  EEPROM.get(EEaddress, floatingpoint_variable);
  EEaddress = EEaddress + sizeof(floatingpoint_variable);
	Serial.print("EEPROM Lecture - Compensation Humidite   : ");
	Serial.println(floatingpoint_variable,2);
	CompensationHumidity = floatingpoint_variable;

//	EEaddress = EEPROMAnythingRead(EEaddress, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));
  EEPROM.get(EEaddress, floatingpoint_variable);
  EEaddress = EEaddress + sizeof(floatingpoint_variable);
	Serial.print("EEPROM Lecture - Compensation Humidite 2 : ");
	Serial.println(floatingpoint_variable,2);
	CompensationHumidity2 = floatingpoint_variable;

//	EEaddress = EEPROMAnythingRead(EEaddress, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));
  EEPROM.get(EEaddress, floatingpoint_variable);
  EEaddress = EEaddress + sizeof(floatingpoint_variable);
	Serial.print("EEPROM Lecture - Compensation Humidite 3 : ");
	Serial.println(floatingpoint_variable,2);
	CompensationHumidity3 = floatingpoint_variable;

//	EEaddress = EEPROMAnythingRead(EEaddress, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));
  EEPROM.get(EEaddress, floatingpoint_variable);
  EEaddress = EEaddress + sizeof(floatingpoint_variable);
	Serial.print("EEPROM Lecture - Compensation Luminosite   : ");
	Serial.println(floatingpoint_variable,2);
	CompensationLight = floatingpoint_variable;

//	EEaddress = EEPROMAnythingRead(EEaddress, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));
  EEPROM.get(EEaddress, floatingpoint_variable);
  EEaddress = EEaddress + sizeof(floatingpoint_variable);
	Serial.print("EEPROM Lecture - Compensation Luminosite 2 : ");
	Serial.println(floatingpoint_variable,2);
	CompensationLight2 = floatingpoint_variable;

//	EEaddress = EEPROMAnythingRead(EEaddress, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));
  EEPROM.get(EEaddress, floatingpoint_variable);
  EEaddress = EEaddress + sizeof(floatingpoint_variable);
	Serial.print("EEPROM Lecture - Compensation Luminosite 3 : ");
	Serial.println(floatingpoint_variable,2);
	CompensationLight3 = floatingpoint_variable;

//	EEaddress = EEPROMAnythingRead(EEaddress, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));
  EEPROM.get(EEaddress, floatingpoint_variable);
  EEaddress = EEaddress + sizeof(floatingpoint_variable);
	Serial.print("EEPROM Lecture - Compensation Pression   : ");
	Serial.println(floatingpoint_variable,2);
	CompensationPressure = floatingpoint_variable;

//	EEaddress = EEPROMAnythingRead(EEaddress, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));
  EEPROM.get(EEaddress, floatingpoint_variable);
  EEaddress = EEaddress + sizeof(floatingpoint_variable);
	Serial.print("EEPROM Lecture - Compensation Pression 2 : ");
	Serial.println(floatingpoint_variable,2);
	CompensationPressure2 = floatingpoint_variable;

//	EEaddress = EEPROMAnythingRead(EEaddress, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));
  EEPROM.get(EEaddress, floatingpoint_variable);
  EEaddress = EEaddress + sizeof(floatingpoint_variable);
	Serial.print("EEPROM Lecture - Compensation Pression 3 : ");
	Serial.println(floatingpoint_variable,2);
	CompensationPressure3 = floatingpoint_variable;

//	EEaddress = EEPROMAnythingRead(EEaddress, reinterpret_cast<char*>(&integer_variable), sizeof(integer_variable));
  EEPROM.get(EEaddress, integer_variable);
  EEaddress = EEaddress + sizeof(floatingpoint_variable);
	Serial.println(integer_variable);
	webserver.timezone = integer_variable;
	Serial.print("Timezone - lecture eeprom : ");
	Serial.println(webserver.timezone);

//	EEaddress = EEPROMAnythingRead(EEaddress, reinterpret_cast<char*>(&integer_variable), sizeof(integer_variable));
  EEPROM.get(EEaddress, integer_variable);
  EEaddress = EEaddress + sizeof(integer_variable);
	Serial.println(integer_variable);
	webserver.summertime = integer_variable;
	Serial.print("Summertime - lecture eeprom : ");
	Serial.println(webserver.summertime);

//	EEaddress = EEPROMAnythingRead(EEaddress, reinterpret_cast<char*>(&integer_variable), sizeof(integer_variable));
  EEPROM.get(EEaddress, integer_variable);
  EEaddress = EEaddress + sizeof(integer_variable);
	Serial.println(integer_variable);
	nbreboot = integer_variable;
	Serial.print("NbReboot - lecture eeprom : ");
	Serial.println(nbreboot);

//	EEaddress = EEPROMAnythingRead(EEaddress, reinterpret_cast<char*>(&integer_variable), sizeof(integer_variable));
  EEPROM.get(EEaddress, integer_variable);
  EEaddress = EEaddress + sizeof(integer_variable);
	Serial.println(integer_variable);
	sondeNumber = integer_variable;
	Serial.print("sondeNumber - lecture eeprom : ");
	Serial.println(sondeNumber);
	sprintf(CapteurID, "%02d", sondeNumber);
	Serial.print("CapteurID - lecture eeprom : ");
	Serial.println(CapteurID);

//	EEaddress = EEPROMAnythingRead(EEaddress, reinterpret_cast<char*>(&webserver.mqtt_server4), sizeof(webserver.mqtt_server4));
  EEPROM.get(EEaddress, webserver.mqtt_server4);
	Serial.print("adresse MQTT - lecture eeprom : ");
	Serial.println(webserver.mqtt_server4);

	Serial.flush();
  EEPROM.end();
}



/*********************************************/
/* initEeproom                               */
/*********************************************/

void Data::initEeproom(void)
{

	Serial.println("Init EEPROM");
	Serial.flush();

//     EEPROM.begin(100);  //EEPROM.begin(Size)
	EEPROM.begin(300);  //EEPROM.begin(Size)
	int EEaddress = 0;
	int integer_variable = 12345;
	EEPROM.put(EEaddress, integer_variable);
	EEaddress = EEaddress + sizeof(integer_variable);

//     EEaddress = EEPROMAnythingWrite(1, reinterpret_cast<char*>(&integer_variable), sizeof(integer_variable));

	float floatingpoint_variable = 123.45;
	EEPROM.put(EEaddress, floatingpoint_variable);
	EEaddress = EEaddress + sizeof(floatingpoint_variable);
//     EEaddress = EEPROMAnythingWrite(EEaddress, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));
	Serial.print("EEPROM - TAG float   : ");
	Serial.println(floatingpoint_variable,2);

	floatingpoint_variable = VERSIONPARAM;
	EEPROM.put(EEaddress, floatingpoint_variable);
	EEaddress = EEaddress + sizeof(floatingpoint_variable);
//     EEaddress = EEPROMAnythingWrite(EEaddress, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));
	Serial.print("EEPROM - Version EEPROM   : ");
	Serial.println(floatingpoint_variable,2);
	VersionParam = floatingpoint_variable;

	floatingpoint_variable = COMPTEMP;
	EEPROM.put(EEaddress, floatingpoint_variable);
	EEaddress = EEaddress + sizeof(floatingpoint_variable);
//     EEaddress = EEPROMAnythingWrite(EEaddress, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));
	Serial.print("EEPROM - Compensation Temperature   : ");
	Serial.println(floatingpoint_variable,2);
	CompensationTemp = floatingpoint_variable;

	floatingpoint_variable = COMPTEMP2;
	EEPROM.put(EEaddress, floatingpoint_variable);
	EEaddress = EEaddress + sizeof(floatingpoint_variable);
	//     EEaddress = EEPROMAnythingWrite(EEaddress, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));
	Serial.print("EEPROM - Compensation Temperature 2 : ");
	Serial.println(floatingpoint_variable,2);
	CompensationTemp2 = floatingpoint_variable;

	floatingpoint_variable = COMPTEMP3;
	EEPROM.put(EEaddress, floatingpoint_variable);
	EEaddress = EEaddress + sizeof(floatingpoint_variable);
	//     EEaddress = EEPROMAnythingWrite(EEaddress, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));
	Serial.print("EEPROM - Compensation Temperature 3 : ");
	Serial.println(floatingpoint_variable,2);
	CompensationTemp3 = floatingpoint_variable;

	floatingpoint_variable = COMPHUMIDITY;
	EEPROM.put(EEaddress, floatingpoint_variable);
	EEaddress = EEaddress + sizeof(floatingpoint_variable);
	//     EEaddress = EEPROMAnythingWrite(EEaddress, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));
	Serial.print("EEPROM - Compensation Humidite   : ");
	Serial.println(floatingpoint_variable,2);
	CompensationHumidity = floatingpoint_variable;

	floatingpoint_variable = COMPHUMIDITY2;
	EEPROM.put(EEaddress, floatingpoint_variable);
	EEaddress = EEaddress + sizeof(floatingpoint_variable);
	//     EEaddress = EEPROMAnythingWrite(EEaddress, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));
	Serial.print("EEPROM - Compensation Humidite 2 : ");
	Serial.println(floatingpoint_variable,2);
	CompensationHumidity2 = floatingpoint_variable;

	floatingpoint_variable = COMPHUMIDITY3;
	EEPROM.put(EEaddress, floatingpoint_variable);
	EEaddress = EEaddress + sizeof(floatingpoint_variable);
	//     EEaddress = EEPROMAnythingWrite(EEaddress, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));
	Serial.print("EEPROM - Compensation Humidite 3 : ");
	Serial.println(floatingpoint_variable,2);
	CompensationHumidity3 = floatingpoint_variable;

	floatingpoint_variable = COMPLIGHT;
	EEPROM.put(EEaddress, floatingpoint_variable);
	EEaddress = EEaddress + sizeof(floatingpoint_variable);
	//     EEaddress = EEPROMAnythingWrite(EEaddress, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));
	Serial.print("EEPROM - Compensation Luminosite   : ");
	Serial.println(floatingpoint_variable,2);
	CompensationLight = floatingpoint_variable;

	floatingpoint_variable = COMPLIGHT2;
	EEPROM.put(EEaddress, floatingpoint_variable);
	EEaddress = EEaddress + sizeof(floatingpoint_variable);
	//     EEaddress = EEPROMAnythingWrite(EEaddress, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));
	Serial.print("EEPROM - Compensation Luminosite 2 : ");
	Serial.println(floatingpoint_variable,2);
	CompensationLight2 = floatingpoint_variable;

	floatingpoint_variable = COMPLIGHT3;
	EEPROM.put(EEaddress, floatingpoint_variable);
	EEaddress = EEaddress + sizeof(floatingpoint_variable);
	//     EEaddress = EEPROMAnythingWrite(EEaddress, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));
	Serial.print("EEPROM - Compensation Luminosite 3 : ");
	Serial.println(floatingpoint_variable,2);
	CompensationLight3 = floatingpoint_variable;

	floatingpoint_variable = COMPPRESSURE;
	EEPROM.put(EEaddress, floatingpoint_variable);
	EEaddress = EEaddress + sizeof(floatingpoint_variable);
	//     EEaddress = EEPROMAnythingWrite(EEaddress, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));
	Serial.print("EEPROM - Compensation Pression   : ");
	Serial.println(floatingpoint_variable,2);
	CompensationPressure = floatingpoint_variable;

	floatingpoint_variable = COMPPRESSURE2;
	EEPROM.put(EEaddress, floatingpoint_variable);
	EEaddress = EEaddress + sizeof(floatingpoint_variable);
	//     EEaddress = EEPROMAnythingWrite(EEaddress, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));
	Serial.print("EEPROM - Compensation Pression 2 : ");
	Serial.println(floatingpoint_variable,2);
	CompensationPressure2 = floatingpoint_variable;

	floatingpoint_variable = COMPPRESSURE3;
	EEPROM.put(EEaddress, floatingpoint_variable);
	EEaddress = EEaddress + sizeof(floatingpoint_variable);
	//     EEaddress = EEPROMAnythingWrite(EEaddress, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));
	Serial.print("EEPROM - Compensation Pression 3 : ");
	Serial.println(floatingpoint_variable,2);
	CompensationPressure3 = floatingpoint_variable;

	integer_variable = TIMEZONE;
	EEPROM.put(EEaddress, integer_variable);
	EEaddress = EEaddress + sizeof(integer_variable);
	//     EEaddress = EEPROMAnythingWrite(EEaddress, reinterpret_cast<char*>(&integer_variable), sizeof(integer_variable));
	Serial.print("EEPROM - Timezone   : ");
	Serial.println(integer_variable);
	webserver.timezone = integer_variable;

	integer_variable = SUMMERTIME;
	EEPROM.put(EEaddress, integer_variable);
	EEaddress = EEaddress + sizeof(integer_variable);
	//     EEaddress = EEPROMAnythingWrite(EEaddress, reinterpret_cast<char*>(&integer_variable), sizeof(integer_variable));
	Serial.print("EEPROM - SummerTime   : ");
	Serial.println(integer_variable);
	webserver.summertime = integer_variable;

	integer_variable = 0;
	EEPROM.put(EEaddress, integer_variable);
	EEaddress = EEaddress + sizeof(integer_variable);
	//     EEaddress = EEPROMAnythingWrite(EEaddress, reinterpret_cast<char*>(&integer_variable), sizeof(integer_variable));
	Serial.print("EEPROM - NbReboot   : ");
	Serial.println(integer_variable,2);
	nbreboot = integer_variable;

	integer_variable = atoi(CAPTEURID);
	EEPROM.put(EEaddress, integer_variable);
	EEaddress = EEaddress + sizeof(integer_variable);
	//     EEaddress = EEPROMAnythingWrite(EEaddress, reinterpret_cast<char*>(&integer_variable), sizeof(integer_variable));
	Serial.print("EEPROM - Numsonde   : ");
	Serial.println(integer_variable);
	sondeNumber = integer_variable;

	strcpy(webserver.mqtt_server4,"");
	//     EEaddress = EEPROMAnythingWrite(EEaddress, reinterpret_cast<char*>(&webserver.mqtt_server4), sizeof(webserver.mqtt_server4));
	EEPROM.put(EEaddress, webserver.mqtt_server4);
	EEaddress += 17;
	Serial.print("EEPROM - adresse Mqtt : ");
	Serial.println(webserver.mqtt_server4);

	EEPROM.commit();
	integer_variable = 0;
	Serial.print("sondeNumber - init eeprom : ");
	Serial.print(sondeNumber);   
	Serial.print("   -    ");
	Serial.println(CapteurID);   
	EEPROM.end();
}

/*********************************************/
/* EEPROMAnythingWrite                       */
/*********************************************/

// Write any data structure or variable to EEPROM
int Data::EEPROMAnythingWrite(int pos, char *valeur, int longueur)
{
  for (int i = 0; i < longueur; i++)
  {
    EEPROM.write(pos + i, *valeur);
    valeur++;
  }
  return pos + longueur;
}

/*********************************************/
/* EEPROMAnythingRead                        */
/*********************************************/
 
// Read any data structure or variable from EEPROM
int Data::EEPROMAnythingRead(int pos, char *zeichen, int lenge)
{
  for (int i = 0; i < lenge; i++)
  {
    *zeichen = EEPROM.read(pos + i);
    zeichen++;
  }
  return pos + lenge;
}
/****************************************************/
/*       MesureMajTemp                              */
/****************************************************/

/*************************************************************/
void Data::MesureMajTemp(float Mesure, int PosTableau) {
/*************************************************************/
     
    float TmpCompensation;
    float TmpTemperature;
    
    if (Tableaufifo[PosTableau].NumCapteur == 1)      TmpCompensation = CompensationTemp;
    else if (Tableaufifo[PosTableau].NumCapteur == 2) TmpCompensation = CompensationTemp2;
    else if (Tableaufifo[PosTableau].NumCapteur == 3) TmpCompensation = CompensationTemp3;
    else                                              TmpCompensation = 0;
    
    TmpTemperature = Mesure + TmpCompensation;
    if ((TmpTemperature < -50) || (TmpTemperature > 150)) {
      TmpTemperature = 0;
      Serial.println("Error!");    
      errormanager.SetErrorCapteur();
    }
    else {                                                
      Tableaufifo[PosTableau].SumValue  += TmpTemperature;  
//      TempValue   += temperature;
    }
    Tableaufifo[PosTableau].Value   = TmpTemperature;

    if (Tableaufifo[PosTableau].NumCapteur == 1)      temperature  = TmpTemperature;
    else if (Tableaufifo[PosTableau].NumCapteur == 2) temperature2 = TmpTemperature;
    else if (Tableaufifo[PosTableau].NumCapteur == 3) temperature3 = TmpTemperature;
    else                                              temperature  = 0;
    
    Serial.print("Temperature Mesurée : ");
    Serial.print(Mesure);
    Serial.print(" / compensée : ");
    Serial.print(TmpTemperature);
    Serial.print(" / ");
    Serial.println(TmpCompensation);

  }

/*************************************************************/
  void Data::MesureMajHumidity(float Mesure, int PosTableau) {
/*************************************************************/

   float TmpCompensation;
   float TmpHumidity;

   Serial.print("NumCapteur : ");
   Serial.println(Tableaufifo[PosTableau].NumCapteur);  
   
   if (Tableaufifo[PosTableau].NumCapteur == 1)       TmpCompensation = CompensationHumidity;
    else if (Tableaufifo[PosTableau].NumCapteur == 2) TmpCompensation = CompensationHumidity2;
    else if (Tableaufifo[PosTableau].NumCapteur == 3) TmpCompensation = CompensationHumidity3;
    else                                              TmpCompensation = 0;

    Serial.print("compensation Humidité : ");
    Serial.println(TmpCompensation);  
    
    TmpHumidity    = Mesure + TmpCompensation;
    if ((TmpHumidity < 0) || (TmpHumidity > 100)) {
       TmpHumidity = 0;
       errormanager.SetErrorCapteur();
       Serial.println("Error Humidité en dehors des limites !");    
    }
    else {                                           
//      HumidityValue   += humidity;
      Tableaufifo[PosTableau].SumValue += TmpHumidity;
    }
    
    Tableaufifo[PosTableau].Value   = TmpHumidity;

    if (Tableaufifo[PosTableau].NumCapteur == 1)      humidity  = TmpHumidity;
    else if (Tableaufifo[PosTableau].NumCapteur == 2) humidity2 = TmpHumidity;
    else if (Tableaufifo[PosTableau].NumCapteur == 3) humidity3 = TmpHumidity;
    else                                              humidity  = 0;

    Serial.print("Humidite : ");
    Serial.print(TmpHumidity);
    Serial.print(" - ");
    Serial.println(TmpCompensation);
  }
  

/*************************************************************/
void Data::MesureMajLight(float Mesure, int PosTableau) {
/*************************************************************/

   float TmpCompensation;
   float TmpLux;
 
   if (Tableaufifo[PosTableau].NumCapteur == 1)       TmpCompensation = CompensationLight;
    else if (Tableaufifo[PosTableau].NumCapteur == 2) TmpCompensation = CompensationLight2;
    else if (Tableaufifo[PosTableau].NumCapteur == 3) TmpCompensation = CompensationLight3;
    else                                              TmpCompensation = 0;
      
    TmpLux    = Mesure + TmpCompensation;
    if ((TmpLux < 0) || (TmpLux > 3000)) {
       TmpLux = 0;
       errormanager.SetErrorCapteur();
       Serial.println("Error!");    
    }
    else {                                           
//      LightValue   += lux;
      Tableaufifo[PosTableau].SumValue += TmpLux;
    }
    Tableaufifo[PosTableau].Value   = TmpLux;

    if (Tableaufifo[PosTableau].NumCapteur == 1)      lux  = TmpLux;
    else if (Tableaufifo[PosTableau].NumCapteur == 2) lux2 = TmpLux;
    else if (Tableaufifo[PosTableau].NumCapteur == 3) lux3 = TmpLux;
    else                                              lux  = 0;
    
    Serial.print("Luminosite : ");
    Serial.print(TmpLux);
    Serial.print(" - ");
    Serial.println(TmpCompensation);
}


/*************************************************************/
void Data::MesureMajPressure(float Mesure, int PosTableau) {
/*************************************************************/

   float TmpCompensation;
   float TmpPressure;
  
   if (Tableaufifo[PosTableau].NumCapteur == 1)       TmpCompensation = CompensationPressure;
    else if (Tableaufifo[PosTableau].NumCapteur == 2) TmpCompensation = CompensationPressure2;
    else if (Tableaufifo[PosTableau].NumCapteur == 3) TmpCompensation = CompensationPressure3;
    else                                              TmpCompensation = 0;
    
      
    TmpPressure    = Mesure + TmpCompensation;
    if ((TmpPressure < 0) || (TmpPressure > 1500)) {
       TmpPressure = 0;
       errormanager.SetErrorCapteur();
       Serial.println("Error!");    
    }
    else {                                           
//      PressureValue += pressure;
      Tableaufifo[PosTableau].SumValue += TmpPressure;
    }
    
    Tableaufifo[PosTableau].Value    = TmpPressure;

    if (Tableaufifo[PosTableau].NumCapteur == 1)      pressure  = TmpPressure;
    else if (Tableaufifo[PosTableau].NumCapteur == 2) pressure2 = TmpPressure;
    else if (Tableaufifo[PosTableau].NumCapteur == 3) pressure3 = TmpPressure;
    else                                              pressure  = 0;

    Serial.print("Pression : ");
    Serial.print(TmpPressure);
    Serial.print(" - ");
    Serial.println(TmpCompensation);
}


/*************************************************************/
void Data::SaveEepromNbreboot(int Nbreboot) {
/*************************************************************/

/*  EEPROM.begin(100);  //EEPROM.begin(Size)
  int EEaddress = 0;
  int integer_variable = 0;
  
  integer_variable = 12345;
//    EEaddress += EEPROM.put(EEaddress, integer_variable);
  EEaddress = data.EEPROMAnythingWrite(1, reinterpret_cast<char*>(&integer_variable), sizeof(integer_variable));


  integer_variable = Nbreboot;
  float floatingpoint_variable;
  EEaddress = EEaddress + (sizeof(floatingpoint_variable) * 13)+(sizeof(integer_variable)*2);
//    EEaddress += EEPROM.put(EEaddress, integer_variable);
  EEaddress = data.EEPROMAnythingWrite(EEaddress, reinterpret_cast<char*>(&integer_variable), sizeof(integer_variable));*/
	
	
	EEPROM.begin(300);  //EEPROM.begin(Size)
	int EEaddress = 0;
	int integer_variable = 12345;
	EEPROM.put(EEaddress, integer_variable);
	EEaddress = EEaddress + sizeof(integer_variable);

//     EEaddress = EEPROMAnythingWrite(1, reinterpret_cast<char*>(&integer_variable), sizeof(integer_variable));

	float floatingpoint_variable = 123.45;
	EEPROM.put(EEaddress, floatingpoint_variable);
	EEaddress = EEaddress + sizeof(floatingpoint_variable);
//     EEaddress = EEPROMAnythingWrite(EEaddress, reinterpret_cast<char*>(&floatingpoint_variable), sizeof(floatingpoint_variable));
	Serial.print("EEPROM - TAG float   : ");
	Serial.println(floatingpoint_variable,2);
	
  integer_variable = Nbreboot;
  EEaddress = EEaddress + (sizeof(floatingpoint_variable) * 13)+(sizeof(integer_variable)*2);
  EEaddress += EEPROM.put(EEaddress, integer_variable);
	           
  EEPROM.commit();
  EEPROM.end();
}