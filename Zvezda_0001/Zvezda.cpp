#include "Arduino.h"
#include "Zvezda.h"

#define Tac1 14
#define Tac2 15
#define Tac3 16

#define M2_Pwm1 6
#define M2_Pwm2 5
#define M1_Pwm1 10
#define M1_Pwm2 9

#define UL1 12 //Twice Led
#define UL2 13 //Single Led
#define UL3 17 //RX Led
#define UL4 30 //TX Led

String  ZvezdaReadString;
int     leftSpeedCur;
int     rightSpeedCur;

ZvezdaClass::ZvezdaClass() {
  pinMode(Tac1,    INPUT);
  pinMode(Tac2,    INPUT);
  pinMode(Tac3,    INPUT);
  pinMode(M1_Pwm1, OUTPUT);
  pinMode(M1_Pwm2, OUTPUT);
  pinMode(M2_Pwm1, OUTPUT);
  pinMode(M2_Pwm2, OUTPUT);
  pinMode(UL1,     OUTPUT);
  pinMode(UL2,     OUTPUT);
  pinMode(UL3,     OUTPUT);
  pinMode(UL4,     OUTPUT);
  digitalWrite(14, HIGH);
  digitalWrite(15, HIGH);
  digitalWrite(16, HIGH);

  leftSpeedCur = 0;
  rightSpeedCur = 0;
}

void ZvezdaClass::Setup() {

}


void ZvezdaClass::Mooving(int _leftSpeed, int _rightSpeed) {

  float leftSpeed  = constrain(_leftSpeed,  -100, 100) * 2.55;
  float rightSpeed = constrain(_rightSpeed, -100, 100) * 2.55;

  if (_leftSpeed > 0) {
    digitalWrite(M1_Pwm2, LOW);
    analogWrite( M1_Pwm1, leftSpeed);
  } else {
    digitalWrite(M1_Pwm1, LOW);
    analogWrite( M1_Pwm2, leftSpeed);
  }

  if (_rightSpeed > 0) {
    digitalWrite(M2_Pwm1, LOW);
    analogWrite( M2_Pwm2, rightSpeed);
  } else {
    digitalWrite(M2_Pwm2, LOW);
    analogWrite( M2_Pwm1, rightSpeed);
  }
}

void ZvezdaClass::InertialMooving(int _leftSpeed, int _rightSpeed) {
  _leftSpeed  = constrain(_leftSpeed*5  - leftSpeedCur*4,  -100, 100);
  _rightSpeed = constrain(_rightSpeed*5 - rightSpeedCur*4, -100, 100);

  leftSpeedCur  = leftSpeedCur*0.9 +  _leftSpeed*0.1;
  rightSpeedCur = rightSpeedCur*0.9 + _rightSpeed*0.1;

  Mooving(leftSpeedCur, rightSpeedCur);
}




void ZvezdaClass::Read_Tact1() {
  return digitalRead(Tac1);
}

void ZvezdaClass::TwiceLed(int Time, int Time2) {
  digitalWrite(UL1, HIGH);
  delay(Time2);
  digitalWrite(UL1, LOW);
  delay(Time);
}

void ZvezdaClass::UserLed_Red(boolean x ) {
  if (x == HIGH) {
    digitalWrite(UL2, HIGH);
  } else if (x == LOW) {
    digitalWrite(UL2, LOW);
  }
}

void ZvezdaClass::UserLed_Green(boolean x ) {
  if (x == HIGH) {
    digitalWrite(UL4, LOW);
  } else if (x == LOW) {
    digitalWrite(UL4, HIGH);
  }
}

void ZvezdaClass::UserLed_Yellow(boolean x ) {
  if (x == HIGH) {
    digitalWrite(UL3, LOW);
  } else if (x == LOW) {
    digitalWrite(UL3, HIGH);
  }

}

void ZvezdaClass::MixLed(int Time) {
  for (int i = 0; i <= Time; i++) {
    digitalWrite(UL2, HIGH);
    digitalWrite(UL1, LOW);
    digitalWrite(UL3, LOW);
    digitalWrite(UL4, LOW);

    delay(50);

    digitalWrite(UL1, LOW);
    digitalWrite(UL3, LOW);
    digitalWrite(UL4, HIGH);

    delay(25);
    digitalWrite(UL4, LOW);
    digitalWrite(UL3, HIGH);
    digitalWrite(UL1, LOW);

    delay(50);

    digitalWrite(UL4, HIGH);
    digitalWrite(UL3, HIGH);
    digitalWrite(UL1, LOW);

    delay(50);

    digitalWrite(UL1, HIGH);
    digitalWrite(UL3, LOW);
    digitalWrite(UL4, HIGH);

    delay(25);

    digitalWrite(UL1, HIGH);
    digitalWrite(UL3, LOW);
    digitalWrite(UL4, LOW);

    delay(50);
  }

  digitalWrite(UL2, LOW);
  digitalWrite(UL3, HIGH);
  digitalWrite(UL4, HIGH);
}

ZvezdaClass Zvezda = ZvezdaClass();
