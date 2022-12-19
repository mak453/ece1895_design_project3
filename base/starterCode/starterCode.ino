#include <RTClib.h>
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
#define BUTTON 51
#define POWER 31

#define width 264
#define height 176

ThinkInk_270_Tricolor_C44 display(EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);

SdFat SD;                             // SD card filesystem
Adafruit_ImageReader_EPD reader(SD);  // Image-reader object, pass in SD filesys

RTC_DS1307 rtc;

uint8_t score = 0;
uint8_t prevButton = 0;
uint8_t dayInitial = 1;

void setup(void) {

  Serial.begin(115200);
  Serial.println("Hello");
  display.begin();
  pinMode(POWER, OUTPUT);
  digitalWrite(POWER, HIGH);
  pinMode(BUTTON, INPUT);
  

  // SD card is pretty straightforward, a single call...
  if (!SD.begin(SD_CS, SD_SCK_MHZ(10))) {  // Breakouts require 10 MHz limit due to longer wires
      Serial.println(F("SD begin() failed"));
    for (;;)
    ;  // Fatal error, do not continue
  }

   if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    rtc.adjust(DateTime(DateTime(2022, 12, 18, 6, 0, 0)));
  }


  display.setRotation(2);  // Set rotation
  display.fillScreen(0);   // and clear screen
  display.clearBuffer();
  reader.drawBMP((char *)"/Dash_0.bmp", display, 0, 0);
  drawDay(dayInitial);
  display.display();
  
}

void loop() {


  // Start night
  if (digitalRead(BUTTON) == HIGH){

    DateTime timeStamp = rtc.now();
    Serial.println(timeStamp.timestamp());
    int avgHR = 0;

    long time = millis();

    int8_t button = readButtons();
    char * fileName;
    char value;

    String t = (String)avgHR;
    char const *n_char = t.c_str();

    display.drawChar(212, 120, n_char[0], EPD_BLACK, EPD_BLACK, 8);
    display.display();


    
    while (button == 0){
      button = readButtons();
      // Get data from tracker
      // Print data to serial 
    } 

    long elapsed = millis() - time; 

    // Only goes to next day after 1 minute
    if (elapsed == 1000*60*1){
      dayInitial++;
      if (dayInitial > 6){
        dayInitial = 0;
      }
      avgHR = getAvgHR();
    }

    switch (button) {
      case 1:
        value = '1';
        score += 1;
        prevButton = 1;
        break;

      case 2:
        value = '2';
        score += 2;
        prevButton = 2;
        break;


      case 3:
        value = '3';
        score += 3;
        prevButton = 3;
        break;

      case 4:
        value = 'Z';    
        score -= prevButton;
        prevButton = 0;
        break;

      default:
        value = 'Z';
    }

    switch (score){
      case 1:
        fileName = "Dash_1.bmp";
        break;

      case 2:
        fileName = "Dash_2.bmp";
        break;

      case 3:
        fileName = "Dash_3.bmp";
        break;

      case 4:
        fileName = "Dash_4.bmp";
        break;

      case 5:
        fileName = "Dash_5.bmp";
        break;

      case 6:
        fileName = "Dash_6.bmp";
        break;

      case 7:
        fileName = "Dash_7.bmp";
        break;

      case 8:
        fileName = "Dash_8.bmp";
        break;

      case 9:
        fileName = "Dash_9.bmp";
        break;

      case 10:
        fileName = "Dash_10.bmp";
        break;

      case 11:
        fileName = "Dash_11.bmp";
        break;

      case 12:
        fileName = "Dash_12.bmp";
        break;

      case 13:
        fileName = "Dash_13.bmp";
        break;

      case 14:
        fileName = "Dash_14.bmp";
        break;

      case 15:
        fileName = "Dash_15.bmp";
        break;

      case 16:
        fileName = "Dash_16.bmp";
        break;

      case 17:
        fileName = "Dash_17.bmp";
        break;

      case 18:
        fileName = "Dash_18.bmp";
        break;

      case 19:
        fileName = "Dash_19.bmp";
        break;

      case 20:
        fileName = "Dash_20.bmp";
        break;

      case 21:
        fileName = "Dash_21.bmp";
        break;

      default:
        fileName = "Dash_0.bmp";
    }

    display.clearBuffer();
    reader.drawBMP((char *)fileName, display, 0, 0);
    drawDay(dayInitial);

    t = (String)avgHR;
    char const *z_char = t.c_str();

    int numDigits = (size_t)(t.c_str())/(size_t)(t.c_str()[0]);
    if (numDigits == 1)
      display.drawChar(212, 120, z_char[0], EPD_BLACK, EPD_BLACK, 8);
    else if (numDigits == 2){
      display.drawChar(210, 120, z_char[0], EPD_BLACK, EPD_BLACK, 8);
      display.drawChar(220, 120, z_char[1], EPD_BLACK, EPD_BLACK, 8);
    } else if (numDigits == 3){
      display.drawChar(205, 120, z_char[0], EPD_BLACK, EPD_BLACK, 8);
      display.drawChar(215, 120, z_char[1], EPD_BLACK, EPD_BLACK, 8);
      display.drawChar(215, 120, z_char[2], EPD_BLACK, EPD_BLACK, 8);      
    }

    if (value != 'Z'){
      display.drawChar(197, 17, value, EPD_BLACK, EPD_BLACK, 8);
    }
    display.display();
  }
}

void drawDay(uint8_t day){
  uint8_t space = 20;
  uint8_t space1 = 15;
    uint8_t start = 25;

    switch (day){
      case 0:
        display.drawChar(start + 0*space, 8, 'S', EPD_BLACK, EPD_BLACK, 2);
        display.drawChar(start + 1*space, 8, 'U', EPD_BLACK, EPD_BLACK, 2);
        display.drawChar(start + 2*space, 8, 'N', EPD_BLACK, EPD_BLACK, 2);
        display.drawChar(start + 3*space, 8, 'D', EPD_BLACK, EPD_BLACK, 2);
        display.drawChar(start + 4*space, 8, 'A', EPD_BLACK, EPD_BLACK, 2);
        display.drawChar(start + 5*space, 8, 'Y', EPD_BLACK, EPD_BLACK, 2);
        break;

      case 1:
        display.drawChar(start + 0*space, 8, 'M', EPD_BLACK, EPD_BLACK, 2);
        display.drawChar(start + 1*space, 8, 'O', EPD_BLACK, EPD_BLACK, 2);
        display.drawChar(start + 2*space, 8, 'N', EPD_BLACK, EPD_BLACK, 2);
        display.drawChar(start + 3*space, 8, 'D', EPD_BLACK, EPD_BLACK, 2);
        display.drawChar(start + 4*space, 8, 'A', EPD_BLACK, EPD_BLACK, 2);
        display.drawChar(start + 5*space, 8, 'Y', EPD_BLACK, EPD_BLACK, 2);
        break;
      
      case 2:
        display.drawChar(start + 0*space, 8, 'T', EPD_BLACK, EPD_BLACK, 2);
        display.drawChar(start + 1*space, 8, 'U', EPD_BLACK, EPD_BLACK, 2);
        display.drawChar(start + 2*space, 8, 'E', EPD_BLACK, EPD_BLACK, 2);
        display.drawChar(start + 3*space, 8, 'S', EPD_BLACK, EPD_BLACK, 2);
        display.drawChar(start + 4*space, 8, 'D', EPD_BLACK, EPD_BLACK, 2);
        display.drawChar(start + 5*space, 8, 'A', EPD_BLACK, EPD_BLACK, 2);
        display.drawChar(start + 6*space, 8, 'Y', EPD_BLACK, EPD_BLACK, 2);
        break;

      case 3:
        start = 15;
        display.drawChar(start + 0*space1, 8, 'W', EPD_BLACK, EPD_BLACK, 2);
        display.drawChar(start + 1*space1, 8, 'E', EPD_BLACK, EPD_BLACK, 2);
        display.drawChar(start + 2*space1, 8, 'D', EPD_BLACK, EPD_BLACK, 2);
        display.drawChar(start + 3*space1, 8, 'N', EPD_BLACK, EPD_BLACK, 2);
        display.drawChar(start + 4*space1, 8, 'E', EPD_BLACK, EPD_BLACK, 2);
        display.drawChar(start + 5*space1, 8, 'S', EPD_BLACK, EPD_BLACK, 2);
        display.drawChar(start + 6*space1, 8, 'D', EPD_BLACK, EPD_BLACK, 2);
        display.drawChar(start + 7*space1, 8, 'A', EPD_BLACK, EPD_BLACK, 2);
        display.drawChar(start + 8*space1, 8, 'Y', EPD_BLACK, EPD_BLACK, 2);
        break;

      case 4:
        display.drawChar(start + 0*space1, 8, 'T', EPD_BLACK, EPD_BLACK, 2);
        display.drawChar(start + 1*space1, 8, 'H', EPD_BLACK, EPD_BLACK, 2);
        display.drawChar(start + 2*space1, 8, 'U', EPD_BLACK, EPD_BLACK, 2);
        display.drawChar(start + 3*space1, 8, 'R', EPD_BLACK, EPD_BLACK, 2);
        display.drawChar(start + 4*space1, 8, 'S', EPD_BLACK, EPD_BLACK, 2);
        display.drawChar(start + 5*space1, 8, 'D', EPD_BLACK, EPD_BLACK, 2);
        display.drawChar(start + 6*space1, 8, 'A', EPD_BLACK, EPD_BLACK, 2);
        display.drawChar(start + 7*space1, 8, 'Y', EPD_BLACK, EPD_BLACK, 2);
        break;

      case 5:
        display.drawChar(start + 0*space, 8, 'F', EPD_BLACK, EPD_BLACK, 2);
        display.drawChar(start + 1*space, 8, 'R', EPD_BLACK, EPD_BLACK, 2);
        display.drawChar(start + 2*space, 8, 'I', EPD_BLACK, EPD_BLACK, 2);
        display.drawChar(start + 3*space, 8, 'D', EPD_BLACK, EPD_BLACK, 2);
        display.drawChar(start + 4*space, 8, 'A', EPD_BLACK, EPD_BLACK, 2);
        display.drawChar(start + 5*space, 8, 'Y', EPD_BLACK, EPD_BLACK, 2);
        break;

      case 6:
        display.drawChar(start + 0*space1, 8, 'S', EPD_BLACK, EPD_BLACK, 2);
        display.drawChar(start + 1*space1, 8, 'A', EPD_BLACK, EPD_BLACK, 2);
        display.drawChar(start + 2*space1, 8, 'T', EPD_BLACK, EPD_BLACK, 2);
        display.drawChar(start + 3*space1, 8, 'U', EPD_BLACK, EPD_BLACK, 2);
        display.drawChar(start + 4*space1, 8, 'R', EPD_BLACK, EPD_BLACK, 2);
        display.drawChar(start + 5*space1, 8, 'D', EPD_BLACK, EPD_BLACK, 2);
        display.drawChar(start + 6*space1, 8, 'A', EPD_BLACK, EPD_BLACK, 2);
        display.drawChar(start + 7*space1, 8, 'Y', EPD_BLACK, EPD_BLACK, 2);
        break;
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

uint8_t getAvgHR(){
  // Once Bluetooth works grabs data from wrist tracker
  return random(60, 75);
}