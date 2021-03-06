/* Not tested code */
#include <Joystick.h>
#define PINS 16

#define ENABLE_ANALOG true
int X1 = A0;
int Y1 = A1;
int X2 = A2;
int Y2 = A3;
int BatterPin = 23;

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
/*A,B,X,Y,L-shift,R-shift,L-trigger,R-trigger,Select,Start,HK,none,up,down,left,right*/
CButton Buttons[PINS] ={3,15,4,14,5,2,16,10,0,1,12,13, 9, 7,8,6};
 
void setup() {
//open console for battery status
   Serial.begin(9600);

//check pins  
  for(int i=0 ; i<PINS ;i++) {
    pinMode(Buttons[i].pin, INPUT_PULLUP);
  }

  Joystick.begin();
  if (ENABLE_ANALOG) {
    Joystick.setXAxisRange(230, -256);
    Joystick.setYAxisRange(160, -256);
    Joystick.setRxAxisRange(-256, 160);
    Joystick.setRyAxisRange(-200, 230);    
  } 
}
 
void JButtonStates() {
  if (ENABLE_ANALOG) {
    Joystick.setXAxis(analogRead(X1) - 512);
    Joystick.setYAxis(analogRead(Y1) - 512);
    Joystick.setRxAxis(analogRead(Y2) - 512);
    Joystick.setRyAxis(analogRead(X2) - 512);    
  }

  
  for (int i = 0; i < PINS; i++) {
    int currentState = !digitalRead(Buttons[i].pin);
     
    if (currentState != Buttons[i].lastState) {
      Joystick.setButton(i, currentState);
      Buttons[i].lastState = currentState;
    }
  }  
}

void BatteryStatus()
{
  int sensorValue = analogRead(BatterPin); //read the A5 pin value
  int voltage = sensorValue * (5.00 / 1024.00) * 100; //convert the value to a true voltage.
  Serial.println(voltage); //print the voltage to tty console
}

void loop() {
  JButtonStates();
  BatteryStatus();
  delay(15);
}
