#include "Adafruit_ThinkInk.h"
#include <Adafruit_ImageReader_EPD.h>  // Image-reading functions

// Comment out the next line to load from SPI/QSPI flash instead of SD card:
#define USE_SD_CARD

#define EPD_DC 9
#define EPD_CS 10
#define SRAM_CS 8
#define EPD_RESET -1
#define EPD_BUSY -1
#define SD_CS 4  // SD card chip select

#define width 264
#define height 176

ThinkInk_270_Tricolor_C44 display(EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);
GFXcanvas1 canvas(width, height);

SdFat SD;                             // SD card filesystem
Adafruit_ImageReader_EPD reader(SD);  // Image-reader object, pass in SD filesys

void setup(void) {

  //Serial.begin(9600);
  display.begin();

  // SD card is pretty straightforward, a single call...
  if (!SD.begin(SD_CS, SD_SCK_MHZ(10))) {  // Breakouts require 10 MHz limit due to longer wires
      //Serial.println(F("SD begin() failed"));
    for (;;)
    ;  // Fatal error, do not continue
  }


  display.setRotation(2);  // Set rotation
  display.fillScreen(0);   // and clear screen
  display.clearBuffer();
  reader.drawBMP((char *)"/Dashboard.bmp", display, 0, 0);
  display.display();
}

void loop() {
  int8_t button = readButtons();
  bool update = false;
  char score;

  switch (button) {
    case 1:
      score = '1';
      //Serial.println("A");
      update = true;
      break;

    case 2:
      score = '2';
      //Serial.println("B");
      update = true;
      break;


    case 3:
      score = '3';
      //Serial.println("C");
      update = true;
      break;

    case 4:
      break;

    default:
      break;
  }

  if (update) {
    display.drawChar(197, 17, score, EPD_BLACK, EPD_BLACK, 8);
    display.display();
    display.clearBuffer();
    reader.drawBMP((char *)"/Dashboard.bmp", display, 0, 0);
  }
}

int8_t readButtons(void) {
  uint16_t reading = analogRead(A3);

  if (reading > 600) {
    return 0;  // no buttons pressed
  }
  if (reading > 400) {
    return 4;  // button D pressed
  }
  if (reading > 250) {
    return 3;  // button C pressed
  }
  if (reading > 125) {
    return 2;  // button B pressed
  }
  return 1;  // button A pressed
}