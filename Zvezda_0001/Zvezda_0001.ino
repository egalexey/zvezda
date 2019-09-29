#include "Zvezda.h"

////// Connected Port of Object Sensors \\\\\\

int LSens = 3 ; ////// Connected Port of  Left Sensor \\\\\\

int LDSens = A3; ////// Connected Port of  Left Diagonal Sensor \\\\\\

int LFSens = A2; ////// Connected Port of  Left Front Sensor \\\\\\

int MSens = 4; ////// Connected Port of  Front Sensor \\\\\\

int RFSens = A1; ////// Connected Port of  Right Front Sensor \\\\\\

int RDSens = A0; ////// Connected Port of  Right Diagonal Sensor \\\\\\

int RSens = 2; ////// Connected Port of  Right Sensor \\\\\\

////// Connected Port of Line Sensors \\\\\\

int LQtr = A5; ////// Connected Port of  Left Line Sensor \\\\\\

int RQtr = A4; ////// Connected Port of  Right Line Sensor \\\\\\

////// Last Value \\\\\\

int LastValue = 0;

////// Connected Port of Tactic Switchs \\\\\\

int DS1 = 16;
int DS2 = 15;
int DS3 = 14;

////// Connected Port of Start Button \\\\\\

int StartPin = 7;

//// User leds

int Led1 = 12;
int Led2 = 13;

// Порог черного цвета
int colorBlack = 100;
int speedTest  = 20;
int speedTestB = -100;


void setup() {
  ////// Led Mix Of Beginning \\\\\\

  Zvezda.MixLed(4);

  ////// Object Sensors \\\\\\

  pinMode(LSens,  INPUT_PULLUP);
  pinMode(LDSens, INPUT_PULLUP);
  pinMode(LFSens, INPUT_PULLUP);
  pinMode(MSens,  INPUT_PULLUP);
  pinMode(RFSens, INPUT_PULLUP);
  pinMode(RDSens, INPUT_PULLUP);
  pinMode(RSens,  INPUT_PULLUP);


  ////// Line Sensors \\\\\\

  pinMode(LQtr, INPUT);
  pinMode(RQtr, INPUT);

  ////// Start Button \\\\\\

  pinMode(StartPin, INPUT);

  ////// Mode Switchs \\\\\\

  pinMode(DS1, INPUT);
  pinMode(DS2, INPUT);
  pinMode(DS3, INPUT);

  ////// Switch Pull-Up \\\\\\

  digitalWrite(DS1, HIGH);
  digitalWrite(DS2, HIGH);
  digitalWrite(DS3, HIGH);

  //delay(200);
}

void loop() {

  if (digitalRead(StartPin) == LOW ) {
    digitalWrite(Led2, HIGH);

    Zvezda.Mooving(speedTest, speedTest);

    if(analogRead(LQtr) < colorBlack && analogRead(RQtr) > colorBlack) {
      Zvezda.Mooving(0, 0);
      delay(10);
      Zvezda.Mooving(speedTestB, speedTestB);
      delay(300);
      Zvezda.TurnRight(100, 400);
    }
    if (analogRead(LQtr) > colorBlack && analogRead(RQtr) < colorBlack) {
      Zvezda.Mooving(0, 0);
      delay(10);
      Zvezda.Mooving(speedTestB, speedTestB);
      delay(300);
      Zvezda.TurnLeft(100, 400);
    }


  } else {
    digitalWrite(Led2, LOW);
    Zvezda.Mooving(0, 0);
    delay(1000);
  }
}
