#include "Adafruit_EEPROM_I2C.h"
#include "Adafruit_FRAM_I2C.h"

/* Example code for the Adafruit I2C EEPROM/FRAM breakout */

/* Connect SCL    to SCL
   Connect SDA    to SDA
   Connect VDD    to 3 - 5V DC
   Connect GROUND to common ground */
   
Adafruit_EEPROM_I2C i2ceeprom;
//Adafruit_FRAM_I2C i2ceeprom;

#define EEPROM_ADDR 0x50  // the default address!

int waterPin = A0;
int f = 0;
int iterator = 0; 
uint8_t buffer[1];  // ints are 1 byte!
  
void setup(void) {
  uint16_t num;
  
  Serial.begin(115200);
  
  if (i2ceeprom.begin(0x50)) {  // you can stick the new i2c addr in here, e.g. begin(0x51);
    Serial.println("Found I2C EEPROM");
  } else {
    Serial.println("I2C EEPROM not identified ... check your connections?\r\n");
    while (1) delay(10);
  }

}

void loop(void) {
  f = analogRead(waterPin);
  
  memcpy(buffer, (void *)&f, 1);
 
//  Serial.println((void*)&f);
  
  Serial.println("Writing float to address 0x00");
  i2ceeprom.write(iterator, buffer, 1);

  i2ceeprom.read(iterator, buffer, 1);
  memcpy((void *)&f, buffer, 1);
  Serial.print("Read back int value: ");
  Serial.println(f);
  iterator ++;
  delay(1000); // 1 sec

 
}
