#include <Joystick.h>
#define PINS 16
#define ENABLE_ANALOG1 true

int BatterPin = 23;
int X1 = A2;
int Y1 = A3;
/*
 * 18 = A0 
 * 19 = A1
 * 20 = A2
 * 21 = A3
 * 22 = A4
 * 23 = A5
 */

// Create Joystick
Joystick_ Joystick(0x05, JOYSTICK_TYPE_GAMEPAD, PINS, 0, 
  true, true, false, false, false, false, false, false, false, false, false);

class CButton {
  public:
  int pin = 0;
  int lastState = 0;
  
  CButton(int p) {
    pin = p;
  }
};
//A,B,X,Y,L-shift,R-shift,L-trigger,R-trigger,Select,Start,HK,none,up,down,left,right
CButton Buttons[PINS] ={8,9,6,12,4,5,11,10,7,13,14,16,3,0,2,1};

void setup() {
//open console for battery status
   Serial.begin(9600);

//check pins  
for(int i=0 ; i<PINS ;i++) {
    pinMode(Buttons[i].pin, INPUT_PULLUP);
  }

  Joystick.begin();
  if (ENABLE_ANALOG1) {
    Joystick.setXAxisRange(256, -256);
    Joystick.setYAxisRange(256, -256);
  }
}

void JButtonStates() {
  if (ENABLE_ANALOG1) {
    Joystick.setXAxis(analogRead(X1) - 512);
    Joystick.setYAxis(analogRead(Y1) - 512);
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
  float voltage = sensorValue * (5.00 / 1023.00) * 100; //convert the value to a true voltage.
  Serial.println(voltage); //print the voltage to tty console
}


void loop() {
  JButtonStates();
BatteryStatus(); 
  delay(25);
}
