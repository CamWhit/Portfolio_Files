#include <Wire.h>

void setup() {
  Wire.begin(); //join I2C bus, master address optional
  //pinMode(21, OUTPUT);
  //pinMode(22, OUTPUT);
  Serial.begin(9600);

}

byte cmd_a[] = {0b10000000, 0b01000000, 0b00100000, 0b00010000, 0b00001000, 0b00000100, 0b00000010, 0b00000001};

byte val = 0;

void loop() {
  /*
  for (int i = 0; i < sizeof(cmd_a) - 1; i++)
  {
    Wire.beginTransmission(byte(0x4D));
    Wire.write(byte(0x00));
    Wire.write(byte(0x80));

    Wire.endTransmission(true);

    delay(500);
  }
  */


  /*
  //*****************************************This Section Operates Perfectly***********************************************
  Wire.beginTransmission(byte(0x4D));
  Wire.write(byte(0x00));
  Wire.write(byte(0x80));

  Wire.endTransmission(true);

  delay(50);
  */

  //Working flip of two bits
  /*
  Wire.beginTransmission(byte(0x4D));
  Wire.write(byte(0x00));
  Wire.write(byte(0x80));

  Wire.endTransmission(true);

  delay(500);

  Wire.beginTransmission(byte(0x4D));
  Wire.write(byte(0x00)); //0x00
  Wire.write(byte(0x01)); //0x01 - first led in A row

  Wire.endTransmission(true);

  delay(500);
  */

  for (int i = 0; i < sizeof(cmd_a); i++)
  { 
    Wire.beginTransmission(0x4D);
    Wire.write(byte(0x00));
    Wire.write(byte(cmd_a[i]));

    Wire.endTransmission(true);

    delay(500);
    
  }

  
  


}

//MAX14661 DATA
