//#include <BLEAdafruitService.h>
#include <Adafruit_MPU6050.h>
#include "DFRobot_Heartrate.h"


// macros
#define heartRatePin A1
#define mpuPinSCL A5
#define mpuPinSDA A4
#define batteryPin 13 

DFRobot_Heartrate heartRate(DIGITAL_MODE);   // ANALOG_MODE or DIGITAL_MODE

Adafruit_MPU6050 motionTracker;
uint8_t maxHeartRate, minHeartRate;
uint8_t maxTemp, minTemp;                       // TEMP IN FARENHEIT
bool newNight = true;
sensors_event_t accel, gyro, temp;

void setup() {
  // put your setup code here, to run once:
  pinMode(batteryPin, OUTPUT);
  Serial.begin(9600);

  pinMode(mpuPinSCL, INPUT);
  pinMode(mpuPinSDA, INPUT);

  motionTracker.setAccelerometerRange(MPU6050_RANGE_8_G);
  motionTracker.setGyroRange(MPU6050_RANGE_500_DEG);
  motionTracker.setFilterBandwidth(MPU6050_BAND_21_HZ);
  motionTracker.setHighPassFilter(MPU6050_HIGHPASS_5_HZ);

  if (!motionTracker.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(30);
    }
  }
}

void loop() {
  Serial.println("Hello");
  // put your main code here, to run repeatedly:
  // digitalWrite(batteryPin, LOW);

  if (newNight){
    int initHeartRate = heartRate.getRate();
    maxHeartRate = initHeartRate;
    minHeartRate = initHeartRate;

    motionTracker.getEvent(&accel, &gyro, &temp);
    //float initTemp = (temp.temperature * 9/5) + 32;
    //maxTemp = initTemp;
    //minTemp = initTemp;

    newNight = false;
  }
  // motionTracker.getEvent(&accel, &gyro, &temp);

  //Serial.println();
  //Serial.println("Temp: " + (String)tempRead());
  Serial.println("HR: " + (String)heartRead());
  motionRead();
  delay(2000);
  
}

void motionRead(){
  motionTracker.getEvent(&accel, &gyro, &temp);

  Serial.println("X: " + (String)accel.acceleration.x);
  Serial.println("Y: " + (String)accel.acceleration.y);
  Serial.println("Z: " + (String)accel.acceleration.z);
  Serial.println();
  Serial.println("X: " + (String)gyro.gyro.x);
  Serial.println("Y: " + (String)gyro.gyro.y);
  Serial.println("Z: " + (String)gyro.gyro.z);
  //Serial.println();
  //Serial.println("Temp: " + (String)(temp.temperature * 9/5 + 32));
  Serial.println();
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
int16_t heartRead(){
  int8_t rateValue = -1;
  long startTime = millis();
  int timeOut = 15*1000;

  do {  
    heartRate.getValue(heartRatePin);   // A1 foot sampled values
    rateValue = heartRate.getRate();   // Get heart rate value  
    delay(20);
  } while((millis()-startTime < timeOut) && (rateValue <= 0));

  if (rateValue > maxHeartRate){
    maxHeartRate = rateValue;
  }
  if (rateValue < minHeartRate){
    minHeartRate = rateValue;  
  }

  return rateValue;
}
