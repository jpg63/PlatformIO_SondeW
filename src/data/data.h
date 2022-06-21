/* data -- 
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
/*    1.0.1    10/01/21    Correction capteurID, Ip serveur mqtt                 */
/*    1.0.2    21/01/21    Modif gestion eeprom                                  */
/*                                                                               */
/*																																							 */
/*********************************************************************************/


#ifndef DATA_H
#define DATA_H

#include <Arduino.h>

#include "settings.h"

class Data
{

public:
  float VersionParam = 0;

	int sondeNumber = 0;  
		
	int nbcapteur = 0;
	record_data_sensor Tableaufifo[10];
	int FifoPos = 0;
	
	int compteurMesure = 0;

	float HumidityValue;
	float LightValue;
	float PressureValue;

	char msg[50];
	char msgTemperature[50];
	char msgHumidite[50];
	char msgLight[50];
	char msgPressure[50];

	float temperature = 0.0;
	float temperature2 = 0.0;
	float temperature3 = 0.0;

	float humidity = 0.0;
	float humidity2 = 0.0;
	float humidity3 = 0.0;

	uint16_t lux = 0;
	uint16_t lux2 = 0;
	uint16_t lux3 = 0;

	float pressure = 0.0;
	float pressure2 = 0.0;
	float pressure3 = 0.0;

	char CapteurName[50];
	char CapteurList[50];
	char CapteurType[50];
	char CapteurID[3] = CAPTEURID;

	float CompensationTemp       = COMPTEMP;
	float CompensationTemp2      = COMPTEMP2;
	float CompensationTemp3      = COMPTEMP3;
	float CompensationHumidity   = COMPHUMIDITY;
	float CompensationHumidity2  = COMPHUMIDITY2;
	float CompensationHumidity3  = COMPHUMIDITY3;
	float CompensationLight      = COMPLIGHT; 
	float CompensationLight2     = COMPLIGHT2; 
	float CompensationLight3     = COMPLIGHT3; 
	float CompensationPressure   = COMPPRESSURE;
	float CompensationPressure2  = COMPPRESSURE2;
	float CompensationPressure3  = COMPPRESSURE3;

	void init(void);
	int  EEPROMAnythingWrite(int pos, char *valeur, int longueur);
	int  EEPROMAnythingRead(int pos, char *zeichen, int lenge);
	void MesureMajTemp(float Mesure, int PosTableau);
  void MesureMajHumidity(float Mesure, int PosTableau);
	void MesureMajLight(float Mesure, int PosTableau);
	void MesureMajPressure(float Mesure, int PosTableau);
	void SaveEepromNbreboot(int Nbreboot);
	void readEeproom(void);
	void initEeproom(void);
};

extern Data data;


#endif
