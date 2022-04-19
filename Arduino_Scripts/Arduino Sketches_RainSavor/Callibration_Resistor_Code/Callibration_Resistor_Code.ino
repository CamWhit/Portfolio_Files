#include <Loom.h>

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

#include <EnableInterrupt.h>
#include <Wire.h>

const byte VR_ADDR = 0x2E;  //I2C address for the AD5246 (variable resistor)
const byte VR_VAL = 40; //out of 127, 1 being the lowest value

//Custom function to communicate with I2C devices on the bus
void send_data(byte addr, byte data) {
  Wire.beginTransmission(addr);

  Wire.write(data);

  Wire.endTransmission(true);
}

void setup() {
  pinMode(5, OUTPUT);
  digitalWrite(5, LOW);
  
  //Begin serial communication as usual
  Loom.begin_serial(true);

  Loom.parse_config(json_config);

  LPrintln("\n** SETUP COMPLETE **");

}

void loop() {
  //delay(100);

//    for (int j = 1; j < 127; j = j + 10)
//    {
        send_data(VR_ADDR, VR_VAL);
//      for (int i = 0; i < 4; i++)
//      {
//        
        Loom.record();
        Loom.display_data();
        Loom.pause(1000);
        //delay(50);
//      }
//    }




}
