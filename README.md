# ECE 1895 Design Project 3
The purpose of this project is to complete part of the University of Pittsburgh's Electrical Engineering ciriculum, where students choose and design a project based on personal interests.

## Design Proposal (11/1/2022)
My project will be a two part sleep tracker that allows the user to log data about each night's sleep and try to quantify it and correlate it with a good or bad night's of rest.

It will consist of a Wrist Tracker and Base. The Wrist Tracker will have a heart rate monitor and gyroscope/accelerometer, this will allow the user to grab information about their heart rate, which is vital to establishing sleep quality because ***insert sleep science here***. The gyroscope/accelerometer will allow the user to get movement information, so if the user was tossing and turning in their sleep then the Wrist Tracker can monitor it. In order to keep the size small and comfortable while sleeping a small Lithium battery will be used to power the Wrist Tracker.

The Wrist Tracker will have Bluetooth to connect to the Base. The Base will have a microphone that monitors the sound level throughout the night, it will also have a ***e-ink (hopefully)*** screen that displays the data logged from the past night. In addition, the Base will have three colored buttons: green, yellow, and red corresponding to good, okay, and bad night of sleep, respectively. This will be the user's sleep quality opinion as it is only based on how the user thinks they slept and doesn't take into account any sensor data. The Base will also have an SD card to store many nights worth of data, because the Base can sit beside the bed, it will just be powered via USB through a wall port.

### Minor Goals/Check Points
If unable to complete all of the proposed design I would like to end the class with the following

- Fully working Wrist Tracker
- Wrist Tracker communicates through Bluetooth to computer sending every sensor read 
- Computer stores each sensor read and allows for multi-night tracking
- Computer software that allows for inputting user sleep quality opinion
- Computer software that plots all sensor reads and evaluates taking into consideration user sleep quality opinion
- Computer software computes a sleep quality rating

### Personal Learning Goals
I've never worked with wireless electronics and would like to test myself with Bluetooth communication. Additionally, I've never tackled a project of this size or complexity so I understand it may not be do-able within the time frame (6 weeks). 

Table of Pros/Cons that may lead to successful completion of all goals
| Pros         | Cons |
|--------------|:-----:|
| <p> Chose all breakout components <p> No PCB designing <p> Plenty of sample software for sensors <p> Only doing READs from sensors| <p> Limited time (6 weeks) <p> First Motherboard choice out of order <p> Lots of coding to create a communication and data logger <p> No refined plans for casings of Wrist Tracker or Base <p> Yellow button out of order| 

---

## Update (11/17/2022)

### Wrist Tracker
DFRobot_Heartrate.cpp file modified because value to determine heart rate was too high and heart rate kept registering as 0 BPM (NOT REALISTIC)



### Base Station

| Task | Status | Notes/Future Planning |
|------|--------|:---------------:|
| Make Dashboard graphic |  Basic outline completed | Uses bitMaps to load images from SD cards |
|Added basic user sleep score functionality| Updates Dashboard with sleep score, but does NOT store the value | Will need to figure out an efficient way to draw triangle for weekly sleep score without having to generate each image individually or can make a bunch of options and load onto SD card |
| Purchased Ardiuno Mega clone |Awaiting shipment|Basic sketch for eInk display took up 83% of storage and needed to switch from ATMEGA328P to ATMEGA2560-16au. This increases the amount of sketch memory by about 8 times |



