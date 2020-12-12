#include "fish.h"

Fish::Fish() {
  AFMS = Adafruit_MotorShield();
  bodyMotor = AFMS.getMotor(1);
  mouthMotor = AFMS.getMotor(2);
}

void Fish::begin() {
  AFMS.begin();
  bodyMotor->run(RELEASE);
  mouthMotor->run(RELEASE);

  bodyMotor->setSpeed(255);
  mouthMotor->setSpeed(255);
}

void Fish::head() {
  bodyMotor->run(FORWARD);
}

void Fish::tail() {
  bodyMotor->run(BACKWARD);
}

void Fish::rest() {
  bodyMotor->run(RELEASE);
}

void Fish::setMouth(int state) {
  if (state) {
    mouthMotor->run(FORWARD);
  } else {
    mouthMotor->run(RELEASE);
  }
}
