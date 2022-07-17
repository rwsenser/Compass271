// rws271Compass based on Compass_header_example_ver_0_2 by helscream, see below
// Note: this file based on separate RWS Teensy3.2 work...
// 
/*
MIT License

Copyright (c) 2022 rwsenser

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
//
// RWS note:
// 
//  Board: Adafruit Trinket M0 or UNO
//  Programmer: Arduino ISP
//
// for info on compass.* and its author, Google this string "Omer Ikram ul Haq compass"
//
/* Compass.* Author = helscream (Omer Ikram ul Haq)
Last edit date = 2014-06-22
Website: http://hobbylogs.me.pn/?p=17
Location: Pakistan
Ver: 0.1 beta --- Start
Ver: 0.2 beta --- Debug feature included
*/
//
// 2022-07-06: Verified source code works with Adafruit M0 Trinket
//             and protoboard OLED display using this exact code
//
// 2021-12-23: Add OLED display
//
// 2021-12-08: Added D271comp namespace to compass.h and compass.coo
//
// 2021-12-06:
// Mugged compass.cpp to support Teensy (changed data type)
// Once calibrated, works and has some sense of direction!!
//

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "rwsD271.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

D271 myD271;

const int BLINK1_PIN=13;
const int BLINK2_PIN=0;

// Main code -----------------------------------------------------------------
void setup(){
  Serial.begin(9600);
  
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }  
  display.clearDisplay();
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(WHITE); // Draw white text
  display.cp437(true);         // Use full 256 char 'Code Page 437' font
  
  display.setCursor(0, 0);     // Start at top-left corner
  display.print("CALIBRATE:");
  display.setCursor(0, 10);     // Next down a line   
  display.print("Rotate 3 full times");
  display.display();  
    
  myD271.begin(BLINK1_PIN, BLINK2_PIN);

  
#if 0
  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  // Draw a single pixel in white
  display.drawPixel(10, 10, WHITE);

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();
  delay(2000);
#endif    
}

// Main loop -----------------------------------------------------------------
void loop(){

  myD271.loop();
  
  // myD271.t = millis();

  Serial.print ("Heading angle = ");
  // Serial.print (bearing);
  Serial.print(myD271.getHeading());
  Serial.println(" Degrees");
  display.clearDisplay();
  display.setTextSize(2);      // Normal 1:1 pixel scale
  display.setTextColor(WHITE); // Draw white text
  display.setCursor(0, 0);  
  display.print(360 - myD271.getHeading());
  display.display();  

  delay(500);
    
}
