#include "fish.h"

Fish fish;

void setup() {
  // put your setup code here, to run once:
  fish.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  fish.head();
  delay(1000);
  fish.tail();
  delay(1000);
  fish.rest();
  delay(1000);
  fish.setMouth(1);
  delay(1000);
  fish.setMouth(0);
  delay(1000);
}
