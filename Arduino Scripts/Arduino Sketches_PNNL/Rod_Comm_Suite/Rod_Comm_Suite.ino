#include <Wire.h>

//Define all of the possible rings
//Defining Rings
#define RING1 0
#define RING2 1
#define RING3 2
#define RING4 3
#define RING5 4
#define RING6 5
#define RING7 6
#define RING8 7
#define RING9 8
#define RING10 9
#define RING11 10
#define RING12 11
#define RING13 12
#define RING14 13
#define RING15 14
#define RING16 15

//Going to assume that two rings are connected to a single PCB, only eight devices will need to be used to address the 16 rings. This can be changed in the future
//Ring addresses
const byte RING_ADDR[] = {};

//Define all of the possible OsmoPods
#define POD1 0
#define POD2 1
#define POD3 2
#define POD4 3
#define POD5 4

//Each OsmoPod will fully take one of the PCBs
//OsmoPod Addresses
const byte POD_ADDR[] = {};


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
