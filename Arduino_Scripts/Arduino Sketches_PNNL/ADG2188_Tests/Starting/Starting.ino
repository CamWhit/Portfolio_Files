#include <Wire.h>

const byte DEVICE_ADDR = 0x2E;

const byte bit_mask[] = {};

void send_data(byte data) {
  Wire.beginTransmission(DEVICE_ADDR);

  Wire.write(data);

  Wire.endTransmission(true);
}


void setup() {
  Wire.begin(); //join I2C bus, master address optional

 

}

void loop() {   
  send_data(0x00);
}

//Default address of the switch is 0x77
//77,80,01 should connect X0 and Y0
