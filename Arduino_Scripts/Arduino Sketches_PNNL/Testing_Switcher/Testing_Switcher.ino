#include <Wire.h>

//functions to control a bus of I2C switches (only 8 for now, add multiplexer later)
//always assume that X0 is being connected to Y0-Y3 (only need the four switches)

#define RING1 0
#define RING2 1


const byte ADG_ADDRESSES[] = {0x76,0x77};

//X0 to Y0, X0 to Y1, X0 to Y2, X0 to Y3
const byte WIRE_CONN_ON[] = {0x80, 0x81, 0x82, 0x83};
const byte WIRE_CONN_OFF[] = {0x00, 0x01, 0x02, 0x03};

//const byte GENERIC_SWITCH_CONNS[][2] = {{0x80, 0x00}, {0x89, 0x09}, {0x92, 0x12}, {0x9B, 0x1B}, {0xA4, 0x24}, {0xAD, 0x2D}, {0xC6, 0x86}, {0xCF, 0x8F}};

//const byte LDSW_bit[] = {0x01, 0x00}; //0x01 connects switches immediately, 0x00 latches next switch state until a 0x01 is sent updating all switches at once

//int rs;


void send_data(byte dev, byte reg, byte data = 0x01) {
  Wire.beginTransmission(dev);

  Wire.write(reg);
  Wire.write(data);
 
  Wire.endTransmission(true);
}

void write_ring(int ring, int input) {
  //whic ring, which input to connect
  send_data(ADG_ADDRESSES[ring], WIRE_CONN_ON[input]);
  
}

void clear_switch(int ring) {
  //send_data(ADG_ADDRESSES[ring], WIRE_CONN_OFF[0]);
  //send_data(ADG_ADDRESSES[ring], WIRE_CONN_OFF[1]);
  //send_data(ADG_ADDRESSES[ring], WIRE_CONN_OFF[2]);
  //send_data(ADG_ADDRESSES[ring], WIRE_CONN_OFF[3]);
  send_data(ADG_ADDRESSES[ring],0x10,0x00);
  send_data(ADG_ADDRESSES[ring],0x19,0x00);
  send_data(ADG_ADDRESSES[ring],0x22,0x00);
  send_data(ADG_ADDRESSES[ring],0x2B,0x01);
}

void setup() {
  Wire.begin(); //join I2C bus, master address optional


  clear_switch(RING1);

}

void flash_all()
{
    //connect X2 to Y0
  send_data(0x77,0x90,0x00);
  //connect X3 to Y1
  send_data(0x77,0x99,0x00);
  //connect X4 to Y2
  send_data(0x77,0xA2,0x00);
  //connect X5 to Y3
  send_data(0x77,0xAB,0x01);

  delay(500);

  clear_switch(RING2);

  delay(500);
}

void binary_sweep()
{
  clear_switch(RING1);
  //connect X2 to Y0
  send_data(0x76,0x90,0x01);

  delay(250);

  clear_switch(RING1);

  //connect X3 to Y1
  send_data(0x76,0x99,0x01);

   delay(250);

  clear_switch(RING1);

  //connect X2 to Y0
  send_data(0x76,0x90,0x00);
  //connect X3 to Y1
  send_data(0x76,0x99,0x01);

   delay(250);

   clear_switch(RING1);

   //connect X4 to Y2
  send_data(0x76,0xA2,0x01);

  delay(250);

  clear_switch(RING1);

  //connect X2 to Y0
  send_data(0x76,0x90,0x00);
  //connect X4 to Y2
  send_data(0x76,0xA2,0x01);

  delay(250);

  clear_switch(RING1);

  //connect X3 to Y1
  send_data(0x76,0x99,0x00);
  //connect X4 to Y2
  send_data(0x76,0xA2,0x01);

  delay(250);

  clear_switch(RING1);

  //connect X2 to Y0
  send_data(0x76,0x90,0x00);
  //connect X3 to Y1
  send_data(0x76,0x99,0x00);
  //connect X4 to Y2
  send_data(0x76,0xA2,0x01);

  delay(250);


  /////////////////////////////////
  clear_switch(RING1);
  //connect X5 to Y3
  send_data(0x76,0xAB,0x01);

  delay(250);
  
  clear_switch(RING1);
  //connect X2 to Y0
  send_data(0x76,0x90,0x00);
  //connect X5 to Y3
  send_data(0x76,0xAB,0x01);

  delay(250);

  clear_switch(RING1);

  //connect X3 to Y1
  send_data(0x76,0x99,0x00);
  //connect X5 to Y3
  send_data(0x76,0xAB,0x01);

   delay(250);

  clear_switch(RING1);

  //connect X2 to Y0
  send_data(0x76,0x90,0x00);
  //connect X3 to Y1
  send_data(0x76,0x99,0x00);
  //connect X5 to Y3
  send_data(0x76,0xAB,0x01);

   delay(250);

   clear_switch(RING1);

   //connect X4 to Y2
  send_data(0x76,0xA2,0x00);
  //connect X5 to Y3
  send_data(0x76,0xAB,0x01);

  delay(250);

  clear_switch(RING1);

  //connect X2 to Y0
  send_data(0x76,0x90,0x00);
  //connect X4 to Y2
  send_data(0x76,0xA2,0x00);
  //connect X5 to Y3
  send_data(0x76,0xAB,0x01);

  delay(250);

  clear_switch(RING1);

  //connect X3 to Y1
  send_data(0x76,0x99,0x00);
  //connect X4 to Y2
  send_data(0x76,0xA2,0x00);
  //connect X5 to Y3
  send_data(0x76,0xAB,0x01);

  delay(250);

  clear_switch(RING1);

  //connect X2 to Y0
  send_data(0x76,0x90,0x00);
  //connect X3 to Y1
  send_data(0x76,0x99,0x00);
  //connect X4 to Y2
  send_data(0x76,0xA2,0x00);
  //connect X5 to Y3
  send_data(0x76,0xAB,0x01);

  delay(250);

}



void LED_switch_cascade()
{
  //address of cascaded unit is 0x77
  //turn on the I2C switches
  //connect X0-Y4
  send_data(0x76,0x84,0x00);
  //connecct X1-Y5
  send_data(0x76,0x8D,0x01);

  delay(100);
  //Now communicate with the cascaded I2C device
  //Turn on the LED from the second switch - connect X2-Y0
  send_data(0x77,0x90,0x01);
}

void cascade_flash_all()
{
  //turn on the I2C switches
  //connect X0-Y4
  send_data(0x76,0x84,0x00);
  //connecct X1-Y5
  send_data(0x76,0x8D,0x01);
  
    //connect X2 to Y0
  send_data(0x77,0x90,0x00);
  //connect X3 to Y1
  send_data(0x77,0x99,0x00);
  //connect X4 to Y2
  send_data(0x77,0xA2,0x00);
  //connect X5 to Y3
  send_data(0x77,0xAB,0x01);

  delay(500);

  clear_switch(RING2);

  delay(500);
}

void cascade_binary_sweep()
{
  //turn on the I2C switches
  //connect X0-Y4
  send_data(0x76,0x84,0x00);
  //connecct X1-Y5
  send_data(0x76,0x8D,0x01);

  
  clear_switch(RING2);
  //connect X2 to Y0
  send_data(0x77,0x90,0x01);

  delay(250);

  clear_switch(RING2);

  //connect X3 to Y1
  send_data(0x77,0x99,0x01);

   delay(250);

  clear_switch(RING2);

  //connect X2 to Y0
  send_data(0x77,0x90,0x00);
  //connect X3 to Y1
  send_data(0x77,0x99,0x01);

   delay(250);

   clear_switch(RING2);

   //connect X4 to Y2
  send_data(0x77,0xA2,0x01);

  delay(250);

  clear_switch(RING2);

  //connect X2 to Y0
  send_data(0x77,0x90,0x00);
  //connect X4 to Y2
  send_data(0x77,0xA2,0x01);

  delay(250);

  clear_switch(RING2);

  //connect X3 to Y1
  send_data(0x77,0x99,0x00);
  //connect X4 to Y2
  send_data(0x77,0xA2,0x01);

  delay(250);

  clear_switch(RING2);

  //connect X2 to Y0
  send_data(0x77,0x90,0x00);
  //connect X3 to Y1
  send_data(0x77,0x99,0x00);
  //connect X4 to Y2
  send_data(0x77,0xA2,0x01);

  delay(250);


  /////////////////////////////////
  clear_switch(RING2);
  //connect X5 to Y3
  send_data(0x77,0xAB,0x01);

  delay(250);
  
  clear_switch(RING2);
  //connect X2 to Y0
  send_data(0x77,0x90,0x00);
  //connect X5 to Y3
  send_data(0x77,0xAB,0x01);

  delay(250);

  clear_switch(RING2);

  //connect X3 to Y1
  send_data(0x77,0x99,0x00);
  //connect X5 to Y3
  send_data(0x77,0xAB,0x01);

   delay(250);

  clear_switch(RING2);

  //connect X2 to Y0
  send_data(0x77,0x90,0x00);
  //connect X3 to Y1
  send_data(0x77,0x99,0x00);
  //connect X5 to Y3
  send_data(0x77,0xAB,0x01);

   delay(250);

   clear_switch(RING2);

   //connect X4 to Y2
  send_data(0x77,0xA2,0x00);
  //connect X5 to Y3
  send_data(0x77,0xAB,0x01);

  delay(250);

  clear_switch(RING2);

  //connect X2 to Y0
  send_data(0x77,0x90,0x00);
  //connect X4 to Y2
  send_data(0x77,0xA2,0x00);
  //connect X5 to Y3
  send_data(0x77,0xAB,0x01);

  delay(250);

  clear_switch(RING2);

  //connect X3 to Y1
  send_data(0x77,0x99,0x00);
  //connect X4 to Y2
  send_data(0x77,0xA2,0x00);
  //connect X5 to Y3
  send_data(0x77,0xAB,0x01);

  delay(250);

  clear_switch(RING2);

  //connect X2 to Y0
  send_data(0x77,0x90,0x00);
  //connect X3 to Y1
  send_data(0x77,0x99,0x00);
  //connect X4 to Y2
  send_data(0x77,0xA2,0x00);
  //connect X5 to Y3
  send_data(0x77,0xAB,0x01);

  delay(250);

}

void address_conv_flash_all()
{
  byte addr = 0x67;
    //connect X2 to Y0
  send_data(addr,0x90,0x00);
  //connect X3 to Y1
  send_data(addr,0x99,0x00);
  //connect X4 to Y2
  send_data(addr,0xA2,0x00);
  //connect X5 to Y3
  send_data(addr,0xAB,0x01);

  delay(500);

  send_data(addr,0x10,0x00);
  send_data(addr,0x19,0x00);
  send_data(addr,0x22,0x00);
  send_data(addr,0x2B,0x01);

  delay(500);
}


void loop() {   
  //flash_all();
  //binary_sweep();
  //LED_switch_cascade();
  //cascade_flash_all();
  //cascade_binary_sweep();
  //address_conv_flash_all();
  send_data(0x70,0x80,0x01);

}

//Default address of the switch is 0x77
//77,80,01 should connect X0 and Y0
