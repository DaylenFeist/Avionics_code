
#include "Adafruit_FRAM_I2C.h"
#include <Wire.h>

Adafruit_FRAM_I2C fram     = Adafruit_FRAM_I2C();

// Global variables
uint16_t addressCounter = 0;
int imuPin = A0;
int temp_sense = A0;


void write_frame(int num_sensors){
  uint8_t syncMSB = 160;
  uint8_t syncLSB = 161;
  fram.write(addressCounter, syncMSB);
  addressCounter ++;
  fram.write(addressCounter, syncLSB);
  addressCounter ++;
  
  for (int i : (num_sensors*2)){
    fram.write(addressCounter, buffer[i]);
    addressCounter ++;
  }
  
}

void clearMem(){
    // dump the entire 32K of memory!
  uint8_t value;
  for (uint16_t a = 0; a < 32768; a++) {
    fram.write(a, 0);
  }
  
}


void takeReading(){
  uint16_t sensVal = analogRead(temp_sense);
  uint8_t sensLSB = lowByte(sensVal);
  uint8_t sensMSB = highByte(sensVal);
  memcpy(buffer[0], (void *) &sensMSB, 1);
  memcpy(buffer[1], (void *) &sensLSB, 1);
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


void loadTo(sd card){
  

}


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
