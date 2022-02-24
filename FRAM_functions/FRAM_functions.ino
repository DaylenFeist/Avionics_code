// this file contains the functions used to read and write frames of data to the FRAM

#include "Adafruit_FRAM_I2C.h"
#include <Wire.h>

// declare the FRAM
Adafruit_FRAM_I2C fram = Adafruit_FRAM_I2C();

// declare global variables
// this is where sensor pins will go
uint16_t addressCounter = 0;
uint8_t syncMSB = 160;
uint8_t syncLSB = 161;
int tempPin = A0;


// FUNCTION: write_frame
//
// DESCRIPTION: writes a frame of sensor data (stored in buffer[] array) to the address given by the value of addressCounter in the FRAM chip.
//              the frame is formatted as: a sync byte of 160, a sync byte of 161, then the sensor data.
// 
// INPUTS: num_sensors - the number of sensors that data has been read from

void write_frame(int num_sensors){
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
  uint16_t sensVal = analogRead(tempPin);
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

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
