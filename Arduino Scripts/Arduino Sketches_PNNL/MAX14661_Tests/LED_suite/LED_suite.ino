#include <Wire.h>

const byte MUX_ADDR = 0x4D;

const byte bit_mask[] = {0b10000000, 0b01000000, 0b00100000, 0b00010000, 0b00001000, 0b00000100, 0b00000010, 0b00000001};

void command_mux(byte reg, byte data) {
  Wire.beginTransmission(MUX_ADDR);

  Wire.write(reg);
  Wire.write(data);

  Wire.endTransmission(true);
}

void unmaskA() {
  command_mux(0x00, 0b00000000);
  command_mux(0x01, 0b00000000);
}

void unmaskB() {
  command_mux(0x02, 0b00000000);
  command_mux(0x03, 0b00000000);
}

void unmaskAll() {
  unmaskA();
  unmaskB();
}

void sweep_A() {
  for (int i = 0; i < sizeof(bit_mask); i++)
  { 
    command_mux(0x00, bit_mask[i]);

    delay(500);
  }
  unmaskAll();

  for (int i = 0; i < sizeof(bit_mask); i++)
  {
    command_mux(0x01, bit_mask[i]);

    delay(500);
  }
  unmaskAll();
  
}

void sweep_B() {
  for (int i = 0; i < sizeof(bit_mask); i++)
  { 
    command_mux(0x02, bit_mask[i]);

    delay(500);
  }
  unmaskAll();

  for (int i = 0; i < sizeof(bit_mask); i++)
  {
    command_mux(0x03, bit_mask[i]);

    delay(500);
  }
  unmaskAll();
}

void sweep_pairAB() {
  for (int i = 0; i < sizeof(bit_mask); i++)
  { 
    command_mux(0x00, bit_mask[i]);
    command_mux(0x03, bit_mask[i]);

    delay(500);
  }
  unmaskAll();

  for (int i = 0; i < sizeof(bit_mask); i++)
  { 
    command_mux(0x01, bit_mask[i]);
    command_mux(0x02, bit_mask[i]);

    delay(500);
  }
  unmaskAll();
}

void allABcombos() {
  int setspeed = 100;
  for (int i = 0; i < sizeof(bit_mask); i++)
  {
    command_mux(0x00, bit_mask[i]);
    for (int j = 0; j < sizeof(bit_mask); j++)
    {
      command_mux(0x02, bit_mask[j]);
      delay(setspeed);
    }
    
    unmaskAll();
    
    command_mux(0x00, bit_mask[i]);
    for (int j = 0; j < sizeof(bit_mask); j++)
    {
      command_mux(0x03, bit_mask[j]);
      delay(setspeed);
    }
    delay(setspeed);
    unmaskAll();
  }

  for (int i = 0; i < sizeof(bit_mask); i++)
  {
    command_mux(0x01, bit_mask[i]);
    for (int j = 0; j < sizeof(bit_mask); j++)
    {
      command_mux(0x02, bit_mask[j]);
      delay(setspeed);
    }
    
    unmaskAll();
    
    command_mux(0x01, bit_mask[i]);
    for (int j = 0; j < sizeof(bit_mask); j++)
    {
      command_mux(0x03, bit_mask[j]);
      delay(setspeed);
    }
    delay(setspeed);
    unmaskAll();
  }
  
}

void setup() {
  Wire.begin(); //join I2C bus, master address optional

  unmaskAll();

}

void loop() {   
  allABcombos();
}

//MAX14661 DATA
