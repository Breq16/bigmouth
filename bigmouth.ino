#include "fish.h"
#include <Adafruit_VS1053.h>
#include <SD.h>
#include <avr/sleep.h>

Fish fish;

Adafruit_VS1053_FilePlayer musicPlayer(-1, 7, 6, 3, 4);

void setup() {
  fish.begin();

  musicPlayer.begin();
  SD.begin(4);

  // volume: 0x00 maximum, 0xFE minimum
  uint16_t volume_dial = analogRead(A0);
  uint8_t volume_byte = 256 - map(volume_dial, 0, 1024, 1, 255);
  musicPlayer.setVolume(volume_byte, volume_byte);
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);
  musicPlayer.startPlayingFile("/track001.mp3"); // (full length version)
  // musicPlayer.startPlayingFile("/track002.mp3"); // (10 second version for testing)

  routine();

  while (!musicPlayer.stopped()) {
    delay(100);
  }

  // Sleep the VS1053
  musicPlayer.setVolume(0xFF, 0xFF);
  musicPlayer.sciWrite(VS1053_REG_CLOCKF, 0x0000);
  musicPlayer.sciWrite(VS1053_REG_AUDATA, 0x0010);

  // Sleep the motors
  fish.sleep();

  // Sleep the AVR
  sleep_enable();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_cpu();
}

void loop() {}
