#include "fish.h"
#include "loudness.h"
#include <Adafruit_VS1053.h>
#include <SD.h>
#include <avr/sleep.h>

Fish fish;

Adafruit_VS1053_FilePlayer musicPlayer(-1, 7, 6, 3, 4);

void setup() {
  fish.begin();

  musicPlayer.begin();
  SD.begin(4);
  musicPlayer.setVolume(20, 20);
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);
  // musicPlayer.startPlayingFile("/track001.mp3"); // (full length version)
  musicPlayer.startPlayingFile("/track002.mp3"); // (10 second version for testing)

  for (byte k = 0; k < strlen_P(loudness); k++) {
    uint8_t ampl = pgm_read_byte_near(loudness + k);
    if (ampl > 128) {
      fish.setMouth(1);
    } else {
      fish.setMouth(0);
    }
    if (ampl > 196) {
      fish.head();
    } else if (ampl > 64) {
      fish.tail();
    } else {
      fish.rest();
    }
    delay(10);
  }

  sleep_enable();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_cpu();
}

void loop() {}
