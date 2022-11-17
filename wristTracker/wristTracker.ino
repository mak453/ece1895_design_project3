//#include <BLEAdafruitService.h>
#include <Adafruit_MPU6050.h>
#include "DFRobot_Heartrate.h"

// macros
#define heartRatePin A1
#define mpuPin0 
#define mpuPin1 
#define batteryPin 13 

DFRobot_Heartrate heartRate(DIGITAL_MODE);   // ANALOG_MODE or DIGITAL_MODE

const int heartThreshold = 800;
const int NUM_SAMPLES = 1530;

Adafruit_MPU6050 motionTracker;
int maxHeartRate, minHeartRate;
int maxTemp, minTemp;                       // TEMP IN FARENHEIT
bool newNight = true;
sensors_event_t accel, gyro, temp;

void setup() {
  // put your setup code here, to run once:
  pinMode(batteryPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //digitalWrite(batteryPin, LOW);

  // if (newNight){
  //   int initHeartRate = heartRate.getRate();
  //   maxHeartRate = initHeartRate;
  //   minHeartRate = initHeartRate;

  //   motionTracker.getEvent(&accel, &gyro, &temp);
  //   float initTemp = (temp.temperature * 9/5) + 32;
  //   maxTemp = initTemp;
  //   minTemp = initTemp;

  //   newNight = false;
  // }
  //motionTracker.getEvent(&accel, &gyro, &temp);

  //Serial.println("Temp: " + (String)tempRead());
  Serial.println(heartRead());
  delay(5*1000);
}

void motionRead(){
  motionTracker.getEvent(&accel, &gyro, &temp);

}

/**
  Reads the temperature from the MPU and sets min and max temp if the curretn temp is higher or lower, respectively

  @return current temperature in Farenheit
*/
int tempRead(){
  motionTracker.getEvent(&accel, &gyro, &temp);

  int currTemp = (temp.temperature * 9/5) + 32;
  if (currTemp > maxTemp){
    maxTemp = currTemp;
  } else if (currTemp < minTemp){
    minTemp = currTemp;
  }

  return currTemp;
}

/**
  Reads heart rate and sets max and min values of heart rate if the current rate is higher or lower. respectively
  @return current heart rate
*/
int heartRead(){
  int rate;
  
  int values[NUM_SAMPLES];
  
  while (analogRead(heartRatePin) < heartThreshold*.75);
  int risingEdges = 1;

  uint32_t startTime = millis();

  for (int i=0; i<NUM_SAMPLES; i++){
    int currVal = analogRead(heartRatePin);
    if (currVal < heartThreshold*.75){
      values[i] = 0;
    } else{
      values[i] = 1;
    }
    delay(10);
  }

  uint32_t endTime = millis();

  for (int i=1; i<NUM_SAMPLES; i++){
    if (values[i] > values[i-1]){
      risingEdges++;
    }
  }
  
  double seconds = (endTime-startTime)/1000.0;
  Serial.println("Seconds: " + (String)seconds);
  Serial.println("Edges: " + (String)risingEdges);

  rate = 60*risingEdges/seconds;

  return rate;
}
