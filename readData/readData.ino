#include "Adafruit_EEPROM_I2C.h"
#include "Adafruit_FRAM_I2C.h"
#include <Wire.h>

/* Example code for the Adafruit I2C EEPROM/FRAM breakout */

/* Connect SCL    to SCL
   Connect SDA    to SDA
   Connect VDD    to 3 - 5V DC
   Connect GROUND to common ground */
   
//Adafruit_EEPROM_I2C i2ceeprom;
Adafruit_FRAM_I2C fram = Adafruit_FRAM_I2C();

#define EEPROM_ADDR 0x50  // the default address!

// Global variables
uint16_t addressCounter = 0;
int temp_sense = A0;
uint8_t buffer[2];  // ints are 1 byte!

void readFrame(){
  uint8_t value;
  uint16_t sensorValue;
  for (uint16_t a = 0; a < 32768; a++){
    value = fram.read(a);
    if(value == 160){
      a = a+1;
      value = fram.read(a);
      if (value == 161){
        a = a+1;
        uint16_t MSB = fram.read(a);
        MSB = MSB << 8;
        a = a+1;
        uint8_t LSB = fram.read(a);
        sensorValue = MSB + LSB;
        Serial.println(sensorValue);
      }
    }
  }
}
  

  
void setup(void) {
  uint16_t num;
  
  Serial.begin(115200);
  
  if (fram.begin(0x50)) {  // you can stick the new i2c addr in here, e.g. begin(0x51);
    Serial.println("Found I2C EEPROM");
  } else {
    Serial.println("I2C EEPROM not identified ... check your connections?\r\n");
    while (1) delay(10);
  }

}

void loop(void) {

  readFrame();
  
  delay(100); // 1 sec

 
}
