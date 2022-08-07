// rws271test based on Compass_header_example_ver_0_2
// 2021-12-06
//
/* Author = helscream (Omer Ikram ul Haq)
Last edit date = 2014-06-22
Website: http://hobbylogs.me.pn/?p=17
Location: Pakistan
Ver: 0.1 beta --- Start
Ver: 0.2 beta --- Debug feature included
*/
//
// recently built with Arduino IDE 1.8.9
// 2022-07-18: Test with UNO worked
// 2022-07-18: Test with Adafruit Trinket M0 likely works,  rws271Compass tested with Trinket M0
// 2022-07-18: Test with Teensy 3.2 worked
//
// 2021-12-08: Added D271comp namespace to compass.h and compass.coo
//
// 2021-12-06:
// Mugged compass.cpp to support Teensy (changed data type)
// Once calibrated, seems to work, have some sense of direction!!
//

#include "rwsD271.h"

D271 myD271;

const int BLINK1_PIN=14;
const int BLINK2_PIN=15;

// Main code -----------------------------------------------------------------
void setup(){
  Serial.begin(9600);
  myD271.begin(BLINK1_PIN, BLINK2_PIN);
}

// Main loop -----------------------------------------------------------------
void loop(){

  myD271.loop();
  
  // myD271.t = millis();

  Serial.print ("Heading angle = ");
  // Serial.print (bearing);
  Serial.print(/* 360 - */ myD271.getHeading());
  Serial.println(" Degrees");

  delay(500);
    
}
