# Wrist Tracker Documentation

This **Wrist Tracker** will compose of two 3D printed boxes that hold the breakout boards for the following features: heart rate monitoring, gyroscope and acceleration monitoring, a battery, and Bluetooth to send logged data to the **Base**.


## **Part Product Pages (Guide Links)**

Here are the parts you will need to build a Wrist Tracker with links to each part's guide page

- Motherboard [Seed Xiao nRF52840](https://www.seeedstudio.com/Seeed-XIAO-BLE-nRF52840-p-5201.html) ([Guide](https://wiki.seeedstudio.com/XIAO_BLE/))
- Heart rate monitor [DFRobot SEN0203](https://www.dfrobot.com/product-1540.html) ([Guide](https://wiki.dfrobot.com/Heart_Rate_Sensor_SKU__SEN0203))
- 6 DOF gyro and accelerometer [DFRobot SEN0142](https://www.dfrobot.com/product-880.html) ([Guide](https://wiki.dfrobot.com/6_DOF_Sensor-MPU6050__SKU_SEN0142_))
- 500mAh Lithium Battery [Adafruit Industries LLC 1578](https://www.adafruit.com/product/1578)
- 3D printed case
- Elastic band


## **Pin Layouts**

**Motherboard**

Front
![Motherboard (Front) Pin Layout](https://files.seeedstudio.com/wiki/XIAO-BLE/pinout2.png)  

Back
![Motherboard (Back) Pin Layout](https://files.seeedstudio.com/wiki/XIAO-BLE/pinout3.png)  

**Heart rate monitor**

Pins: A1, 5V, GND

![Heart rate monitor Board Layout](https://dfimg.dfrobot.com/nobody/wiki/c6c4b8f7f56160050ea5e8fda9c3094e.png)
![Heart rate monitor Pin Connections](https://dfimg.dfrobot.com/nobody/wiki/7345658ef6ade7d2efb3a19d1eb4fd87.png)  

**Gyro/accel**

Pins: 5V, GND, A5/SDA, A6/SLA

![Gyro/accel Pin Connections](https://raw.githubusercontent.com/DFRobot/DFRobotMediaWikiImage/master/Image/6_dof_mpu6050.png)  

---

## Code Overview

---

### Update (11/17/2022)
Modified DFRobot_Heartrate Library because value too high to accurately detect heart rate

Original:

    uint16_t DFRobot_Heartrate::digitalGetRate  (void)
    {
        static uint8_t timeFlag;
        static unsigned long sampleTime[10];
        unsigned long valueTime_;
        uint8_t count_;
        
        if(valueCount_){
            count_ = valueCount_-1;
        }else{
            count_ = SAMPLE_NUMBER-1;
        }
        if((value[valueCount_]>1000)&&(value[count_]<20)){
            nowTim = millis();
            uint32_t difTime =  nowTim - lastTim;
            lastTim = nowTim;
            
            if(difTime>300 || difTime<2000){
                sampleTime[timeFlag++] = difTime;
                if(timeFlag > 9)timeFlag=0;
            }       
            if(0 == sampleTime[9]){
                Serial.println("Wait for valid data !");
                return(0);
            }

            uint32_t Arrange[10]={0};
            for(int i=0;i<10;i++){
                Arrange[i] = sampleTime[i];
            }
            uint32_t Arrange_=0;
            for(int i=9;i>0;i--){
                for(int j=0;j<i;j++){
                    if(Arrange[j] > Arrange[j+1]){
                    Arrange_ = Arrange[j];
                    Arrange[j] = Arrange[j+1];
                    Arrange[j+1] = Arrange_;
                    }
                }
            }
            if((Arrange[7]-Arrange[3])>120){
                Serial.println("Wait for valid data !");
                return(0);
            }

            Arrange_ = 0;
            for(int i=3;i<=7;i++){
                Arrange_ += Arrange[i];
            }

            valueTime_ = 300000/Arrange_;   // 60*1000*(7-2)
            return((uint16_t)valueTime_);
        }
        return(0);

    }

Modified:

    uint16_t DFRobot_Heartrate::digitalGetRate  (void)
    {
        static uint8_t timeFlag;
        static unsigned long sampleTime[10];
        unsigned long valueTime_;
        uint8_t count_;
        
        if(valueCount_){
            count_ = valueCount_-1;
        }else{
            count_ = SAMPLE_NUMBER-1;
        }
        if((value[valueCount_]>800)&&(value[count_]<20)){
            nowTim = millis();
            uint32_t difTime =  nowTim - lastTim;
            lastTim = nowTim;
            
            if(difTime>300 || difTime<2000){
                sampleTime[timeFlag++] = difTime;
                if(timeFlag > 9)timeFlag=0;
            }       
            if(0 == sampleTime[9]){
                Serial.println("Wait for valid data !");
                return(0);
            }

            uint32_t Arrange[10]={0};
            for(int i=0;i<10;i++){
                Arrange[i] = sampleTime[i];
            }
            uint32_t Arrange_=0;
            for(int i=9;i>0;i--){
                for(int j=0;j<i;j++){
                    if(Arrange[j] > Arrange[j+1]){
                    Arrange_ = Arrange[j];
                    Arrange[j] = Arrange[j+1];
                    Arrange[j+1] = Arrange_;
                    }
                }
            }
            if((Arrange[7]-Arrange[3])>120){
                Serial.println("Wait for valid data !");
                return(0);
            }

            Arrange_ = 0;
            for(int i=3;i<=7;i++){
                Arrange_ += Arrange[i];
            }

            valueTime_ = 300000/Arrange_;   // 60*1000*(7-2)
            return((uint16_t)valueTime_);
        }
        return(0);

    }

