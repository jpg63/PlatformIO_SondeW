#include <EEPROM.h>
 
// Write any data structure or variable to EEPROM
int EEPROMAnythingWrite(int pos, char *zeichen, int lenge)
{
  for (int i = 0; i < lenge; i++)
  {
    EEPROM.write(pos + i, *zeichen);
    zeichen++;
  }
  return pos + lenge;
}
 
// Read any data structure or variable from EEPROM
int EEPROMAnythingRead(int pos, char *zeichen, int lenge)
{
  for (int i = 0; i < lenge; i++)
  {
    *zeichen = EEPROM.read(pos + i);
    zeichen++;
  }
  return pos + lenge;
}
 
struct Timer_stuct {
  byte art;
  unsigned long timestamp;
  byte relais;
};
 
void setup()
{
  Serial.begin(115200);
  Serial.println(" ");
  Serial.println("Start");
  EEPROM.begin(255);
 
  // Integer to EEPROM at position 100
  unsigned int zahl_int = 1000;
  int nekst_free = EEPROMAnythingWrite(100, reinterpret_cast<char*>(&zahl_int), sizeof(zahl_int));
 
  // Float to EEPROM
  float   zahl_float = 0.123;
  nekst_free = EEPROMAnythingWrite(nekst_free, reinterpret_cast<char*>(&zahl_float), sizeof(zahl_float));
 
  // Store structure (struct) to EEPROM
  Timer_stuct timer;
  timer.art = 88;
  timer.timestamp = 1485206580;
  timer.relais = 3;
  nekst_free = EEPROMAnythingWrite(nekst_free, reinterpret_cast<char*>(&timer), sizeof(timer));
 
  // Store array to EEPROM
  unsigned long timestamps[2] = {1485206594, 1485206890};
  EEPROMAnythingWrite(nekst_free, reinterpret_cast<char*>(&timestamps), sizeof(timestamps));
 
  EEPROM.commit();
 
  unsigned int zahl2_int = 0;
  float   zahl2_float = 0.0;
  Timer_stuct timer2;
  unsigned long timestamps2[2];
  
  // Integer read from EEPROM
  nekst_free = EEPROMAnythingRead(100, reinterpret_cast<char*>(&zahl2_int), sizeof(zahl2_int));
  
  // Float read to EEPROM
  nekst_free = EEPROMAnythingRead(nekst_free, reinterpret_cast<char*>(&zahl2_float), sizeof(zahl2_float));
  
  // Read structure (struct) from EEPROM
  nekst_free = EEPROMAnythingRead(nekst_free, reinterpret_cast<char*>(&timer2), sizeof(timer2));
  
  // Read array from EEPROM
  EEPROMAnythingRead(nekst_free, reinterpret_cast<char*>(&timestamps2), sizeof(timestamps2));
  
  Serial.println(zahl2_int);
  Serial.println(zahl2_float, 3);
  Serial.println("art = " + String(timer2.art) + " ,timestamp = " + String(timer2.timestamp) + " , relais = " + String(timer2.relais));
  Serial.println("timestamp 1 = " + String(timestamps2[0]) + " , timestamp 2 = " + String(timestamps2[1]));
}
 
void loop()
{
}