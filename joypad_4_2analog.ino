/* Not tested code */
#include <Joystick.h>
#define PINS 14
#define ENABLE_ANALOG true
int X1 = A0;
int Y1 = A1;
int X2 = A2;
int Y2 = A3;
/*
 * 18 = A0
 * 19 = A1
 * 20 = A2
 * 21 = A3
 */
 
// Create Joystick
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_MULTI_AXIS, PINS, 0,
  true, true, false, true, true, false, false, false, false, false, true);
 
class CButton {
  public:
  int pin = 0;
  int lastState = 0;
 
  CButton(int p) {
    pin = p;
  }
};
 
CButton Buttons[PINS] ={0,1,2,3,4,5,6,7,8,9,10,16,14,15};
 
void setup() {
  for(int i=0 ; i<PINS ;i++) {
    pinMode(Buttons[i].pin, INPUT_PULLUP);
  }
 
  Joystick.begin();
  if (ENABLE_ANALOG) {
    Joystick.setXAxisRange(256, -256);
    Joystick.setYAxisRange(256, -256);
    Joystick.setRxAxisRange(-256, 256);
    Joystick.setRyAxisRange(256, -256);    
  } 
}
 
void JButtonStates() {
  if (ENABLE_ANALOG) {
    Joystick.setXAxis(analogRead(X1) - 512);
    Joystick.setYAxis(analogRead(Y1) - 512);
    Joystick.setRxAxis(analogRead(X2) - 512);
    Joystick.setRyAxis(analogRead(Y2) - 512);    
  }

  
  for (int i = 0; i < PINS; i++) {
    int currentState = !digitalRead(Buttons[i].pin);
   
    if (currentState != Buttons[i].lastState) {
      Joystick.setButton(i, currentState);
      Buttons[i].lastState = currentState;
    }
  }  
}
 
void loop() {
  JButtonStates();
  delay(50);
}
