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

void takeReading(){
  uint16_t sensVal = analogRead(temp_sense);
  uint8_t sensLSB = lowByte(sensVal);
  uint8_t sensMSB = highByte(sensVal);
//  memcpy(buffer[0], &sensMSB, 1);
//  memcpy(buffer[1], &sensLSB, 1);
  buffer[0] = sensMSB;
  buffer[1] = sensLSB;
  Serial.println(sensLSB);
}


void write_frame(int num_sensors){
  uint8_t syncMSB = 160;
  uint8_t syncLSB = 161;
  fram.write(addressCounter, syncMSB);
  addressCounter ++;
  fram.write(addressCounter, syncLSB);
  addressCounter ++;
  
  for (int i=0; i < (num_sensors*2); i++){
    fram.write(addressCounter, buffer[i]);
    addressCounter ++;
  }
  
}

void read_frame(){
    // dump the entire 32K of memory!
  uint8_t value;
  for (uint16_t a = 0; a < 32768; a++) {
    value = fram.read(a);
    if ((a % 32) == 0) {
      Serial.print("\n 0x"); Serial.print(a, HEX); Serial.print(": ");
    }
    Serial.print("0x"); 
    if (value < 0x1) 
      Serial.print('0');
    Serial.print(value, HEX); Serial.print(" ");
  }
  
}

void clearMem(){
    // dump the entire 32K of memory!
  uint8_t value;
  for (uint16_t a = 0; a < 32768; a++) {
    fram.write(a, 0);
    if(a%100 == 0){
      Serial.println((float)(a*100/32768));
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
//  clearMem();

}

void loop(void) {

  takeReading();

  write_frame(1);
  
  delay(100); // 1 sec

 
}
