#pragma once

#include <Adafruit_MotorShield.h>

class Fish {
  public:
    Fish();
    void begin();
    void head();
    void tail();
    void rest();
    void setMouth(int state);
    void sleep();
  private:
    Adafruit_MotorShield AFMS;
    Adafruit_DCMotor *bodyMotor;
    Adafruit_DCMotor *mouthMotor;
};
