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

enum State_enum {STOP, FORWARD, ROTATE_RIGHT, ROTATE_LEFT, MOVE_BACK};
enum Sensors_enum {NONE, SENSOR_RIGHT, SENSOR_LEFT, BOTH};

void state_machine_run(uint8_t sensors);
void motors_stop();
void motors_forward();
void motors_right();
void motors_left();
void motors_back();
uint8_t read_IR();
 
uint8_t state   = STOP;
uint8_t Sensors = NONE;



void setup() {
  ////// Led Mix Of Beginning \\\\\\

  Zvezda.MixLed(2);

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

  if (digitalRead(StartPin) == LOW ) 
     {
       digitalWrite(Led2, HIGH);
       
       //Serial.println(Sensors);
       
       Sensors = read_IR();
       
       
       state_machine_run(Sensors);
       delay(5);
       } 
  else 
     {
      digitalWrite(Led2, LOW);
      Zvezda.Mooving(0, 0);
      delay(10);
     }
}

void state_machine_run(uint8_t sensors) 
{
  switch(state)
  {
    case STOP:
      if(sensors == NONE){
        motors_forward();
        state = FORWARD;
      }
      else if(sensors == SENSOR_RIGHT){
        motors_left();
        state = ROTATE_LEFT;
      }
      else if(sensors == SENSOR_LEFT){
        motors_right();
        state = ROTATE_RIGHT;
      }
      else{
        motors_back();
        state = MOVE_BACK;
      }
      break;
       
    case FORWARD:
      if(sensors != NONE){
        motors_stop();
        state = STOP;
      }
      break;
 
    case ROTATE_RIGHT:
      if(sensors == NONE || sensors == SENSOR_RIGHT){
        motors_stop();
        state = STOP;
      }
      break;
 
    case ROTATE_LEFT:
      if(sensors != SENSOR_RIGHT)
      {
        motors_stop();
        state = STOP; 
      }
      break;
    case MOVE_BACK:{
        motors_stop();
        state = STOP; 
     } 
     break;
  }
}
 
void motors_stop()
{
  Zvezda.InertialMooving(0, 0);
  delay(10);
}
 
void motors_forward()
{
  Zvezda.InertialMooving(speedTest, speedTest);
  //Zvezda.Mooving(speedTest, speedTest);
}

void motors_back()
{
  Zvezda.InertialMooving(-speedTest, -speedTest);
  delay(100);
  //Zvezda.Mooving(-20, 20);
  Zvezda.InertialMooving(-20, 20);
  delay(10);
}
 
void motors_right()
{
  //Zvezda.Mooving(-20, 20);
  Zvezda.InertialMooving(-20, 20);
  delay(10);
}
 
void motors_left()
{
  //Zvezda.Mooving(20, -20);
  Zvezda.InertialMooving(20, -20);
  delay(10);
}
 
uint8_t read_IR()
{
 uint8_t sensors = NONE;
   if(analogRead(LQtr) < colorBlack && analogRead(RQtr) > colorBlack) {
     
     //Serial.println("left");
     
     return SENSOR_LEFT;  
    }
    if (analogRead(LQtr) > colorBlack && analogRead(RQtr) < colorBlack) {
      
      //Serial.println("RIGHT");
      
      return SENSOR_RIGHT;
    }
    if(analogRead(LQtr < colorBlack) && analogRead(RQtr) < colorBlack) {
      
      //speedTest = -20; 
      //Serial.println("BOTH");
      
      return BOTH;      
      }
    if(analogRead(LQtr > colorBlack) && analogRead(RQtr) > colorBlack) {
      //speedTest = 20;
     
      //Serial.println("NONE");
      
      return NONE;           
      } 
  return sensors;
}
