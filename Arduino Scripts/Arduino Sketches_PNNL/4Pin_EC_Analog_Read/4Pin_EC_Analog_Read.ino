#include <Loom.h>
#include <Wire.h>

const char* json_config =
#include "config.h"
;

LoomFactory<
  Enable::Internet::Disabled,
  Enable::Sensors::Enabled,
  Enable::Radios::Disabled,
  Enable::Actuators::Disabled,
  Enable::Max::Disabled
>ModuleFactory{};

LoomManager Loom{ &ModuleFactory };


int volt1 = 0;
int volt2 = 0;

void send_data(byte dev, byte reg, byte data = 0x01) {
  Wire.beginTransmission(dev);

  Wire.write(reg);
  Wire.write(data);
 
  Wire.endTransmission(true);
}

void setup() {
  //Serial.begin(9600);

  Loom.begin_serial(true);

  Loom.parse_config(json_config);

  LPrintln("\n** SETUP COMPLETE **");
}

void loop() {
//  volt1 = analogRead(A0);
//  volt2 = analogRead(A1);
//  Serial.print(volt1);
//  Serial.print("_");
//  Serial.println(volt2);
//  delay(1000);

  
    //send_data(0x70,0x90,0x01);
    //connect X3 to Y1
//    send_data(0x70,0x99,0x00);
//    //connect X4 to Y2
//    send_data(0x70,0xA2,0x00);
//    //connect X5 to Y3
//    send_data(0x70,0xAB,0x01);

    delay(500);

    Loom.record();
    Loom.display_data();
    Loom.pause(1000);

}
