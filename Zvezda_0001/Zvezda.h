#ifndef Zvezda_h 
#define Zvezda_h

class ZvezdaClass{ 
  public: 
    ZvezdaClass(); 
    void Setup(); 
    byte mode();
    void Read_Tact1(); 
    // движение робота
    void Mooving(int leftSpeed, int rightSpeed);
    void InertialMooving(int _leftSpeed, int _rightSpeed);
  
    int VoltageIn();
    int Trimpot(); 
    
    void MixLed(int Time);
    
    void TwiceLed(int Time,int Time2);
    
    void UserLed_Red(boolean x);
    void UserLed_Green(boolean x);
    void UserLed_Yellow(boolean x);
};


extern ZvezdaClass Zvezda;

#endif
