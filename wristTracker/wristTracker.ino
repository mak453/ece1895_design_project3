#include <BLEAdafruitService.h>
#include <Adafruit_MPU6050.h>
#include "DFRobot_Heartrate.h"

// macros
#define heartRatePin A1
#define mpuPin0
#define mpuPin1
#define batteryPin P0_13 

DFRobot_Heartrate heartRate(DIGITAL_MODE);   // ANALOG_MODE or DIGITAL_MODE
Adafruit_MPU6050 motionTracker;
int maxHeartRate, minHeartRate;
int maxTemp, minTemp;
bool newNight = true;

void setup() {
  // put your setup code here, to run once:
  pinMode (batteryPin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(batteryPin, LOW);
  
  if (newNight){
    int initHeartRate = heartRate.getRate();
    maxHeartRate = initHeartRate;
    minHeartRate = initHeartRate;

    motionTracker.getEvent(&accel, &gyro, &temp);
    int initTemp = (temp.temperature * 9/5) + 32;
    maxTemp = initTemp;
    minTemp = initTemp;

    newNight = false;
  } else{

  }
}

void motionRead(){
  sensors_event_t accel, gyro, temp;
  motionTracker.getEvent(&accel, &gyro, &temp);
}

/**
  Reads heart rate and sets max and min values of heart rate if the current rate is higher or lower. respectively
  @returns current heart rate
*/
int heartRead(){
  int currRate = heartRate.getRate();

  if (currRate > maxHeartRate){
    maxHeartRate = currRate;
  } else if (currRate < minHeartRate){
    minHeartRate = currRate;
  }

  return currRate;
}
