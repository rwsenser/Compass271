//
// rwsD271.h:  front end (wrapper) for the GY-271 compass
//           used compass(2).h and compass(2).cpp
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
#include <Wire.h>
#include "compass2.h"
//

// 2022-07-17 cleanup
// * improve LED handling

// 2021-12-06/08: created and then added D271comp namespace to compass.h and compass.cpp

// note complex calibration process is "hidden" in compass.cpp

class D271 {

  private:
    int blink1_pin;
    int blink2_pin;

  public: 
    void begin (int _b1, int _b2) {
      // init blinking
      blink1_pin = _b1;
      blink2_pin = _b2;
      if (blink1_pin != 0) {
        pinMode(blink1_pin, OUTPUT); 
        digitalWrite(blink1_pin, HIGH);
      }
      if (blink2_pin != 0) {
        pinMode(blink2_pin, OUTPUT); 
        digitalWrite(blink2_pin, LOW);        
      }  
    
      Wire.begin();
      D271comp::compass_x_offset = 122.17;
      D271comp::compass_y_offset = 230.08;
      D271comp::compass_z_offset = 389.85;
      D271comp::compass_x_gainError = 1.12;
      D271comp::compass_y_gainError = 1.13;
      D271comp::compass_z_gainError = 1.03;
  
      D271comp::compass_init(2, blink1_pin, blink2_pin);
      // D271comp::compass_debug = 1;
      D271comp::compass_offset_calibration(3); 
      // reset LED to green
      if (blink1_pin != 0) {
        digitalWrite(blink1_pin, LOW);
      }
      if (blink2_pin != 0) {  
        digitalWrite(blink2_pin, HIGH);
      }         
    }

    void loop() {
      D271comp::compass_heading();
      // return results in D271comp::bearing variable
    }

    float getHeading() {
      return D271comp::bearing;
    }
};

// D271 myD271;
