#include <Wire.h>

//functions to control a bus of I2C switches (only 8 for now, add multiplexer later)
//always assume that X0 is being connected to Y0-Y3 (only need the four switches)

#define RING1 0
#define RING2 1
#define RING3 2
#define RING4 3
#define RING5 4
#define RING6 5
#define RING7 6
#define RING8 7

const byte ADG_ADDRESSES[] = {0x77, 0x76, 0x75, 0x74, 0x73, 0x72, 0x71, 0x70};
const byte Current_List[] = {0x75, 0x77};

//X0 to Y0, X0 to Y1, X0 to Y2, X0 to Y3
const byte WIRE_CONN_ON[] = {0x80, 0x81, 0x82, 0x83};
const byte WIRE_CONN_OFF[] = {0x00, 0x01, 0x02, 0x03};

//const byte GENERIC_SWITCH_CONNS[][2] = {{0x80, 0x00}, {0x89, 0x09}, {0x92, 0x12}, {0x9B, 0x1B}, {0xA4, 0x24}, {0xAD, 0x2D}, {0xC6, 0x86}, {0xCF, 0x8F}};

//const byte LDSW_bit[] = {0x01, 0x00}; //0x01 connects switches immediately, 0x00 latches next switch state until a 0x01 is sent updating all switches at once

//int rs;

byte conversion  = 0b00000000;
byte confi = 0b00000001;


void send_data(byte dev, byte reg, byte data = 0x01) {
  Wire.beginTransmission(dev);

  Wire.write(reg);
  Wire.write(data);

  Wire.endTransmission(true);
}

void send_data2(byte address = 0x2E, byte reg, byte write_data)
{
  Wire.beginTransmission(address);
}

void write_ring(int ring, int input) {
  //whic ring, which input to connect
  send_data(ADG_ADDRESSES[ring], WIRE_CONN_ON[input]);
  
}

void clear_switch(int ring) {
  send_data(ADG_ADDRESSES[ring], WIRE_CONN_OFF[0]);
  send_data(ADG_ADDRESSES[ring], WIRE_CONN_OFF[1]);
  send_data(ADG_ADDRESSES[ring], WIRE_CONN_OFF[2]);
  send_data(ADG_ADDRESSES[ring], WIRE_CONN_OFF[3]);
}

void setup() {
  Wire.begin(); //join I2C bus, master address optional

 

}

int Ring1 = 0;
int Ring2 = 2;

void loop() {   
  //Dealing with two switches: 0x75,0x77
  //Want to connect X0 to Y0
  write_ring(0,0);
  
}

//Default address of the switch is 0x77
//77,80,01 should connect X0 and Y0
