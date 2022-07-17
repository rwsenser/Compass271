/* Author = helscream (Omer Ikram ul Haq)
Last edit date = 2014-06-22
Website: http://hobbylogs.me.pn/?p=17
Location: Pakistan
Ver: 0.1 beta --- Start
Ver: 0.2 beta --- Debug feature included
*/

// 2021-12-08:  RWS added D271comp namespace, add blink LED while calibrating

#ifndef compass.h
  #define compass.h
  namespace D271comp {  
  #include "compass2.h"

  extern int blink1;
  extern int blink2;
  extern float bearing;
  extern float compass_x_scalled;
  extern float compass_y_scalled;
  extern float compass_z_scalled;
  
  extern float compass_x_offset, compass_y_offset, compass_z_offset;
  extern float compass_x_gainError,compass_y_gainError,compass_z_gainError;
  
  extern int compass_debug;
  
  void compass_read_XYZdata();
  void compass_offset_calibration(int select);
  void compass_init(int gain, int pin1, int pin2);
  void compass_scalled_reading();
  void compass_heading();

  }  
  
#endif
