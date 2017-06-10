#include <Arduino.h>
#include <Thread.h>
#include <ThreadController.h>
#include "DirectionAnalyzer.h"
#include <SPI.h>
#include "WifiConnector.h"

#define TRIGGER 5
#define ECHO 4
#define TRIGGER2 14
#define ECHO2 12

#define SPEAKER 13

long durationOne, distanceOne;
long durationTwo, distanceTwo;
bool connected = false;


Thread threadOne = Thread();
Thread threadTwo = Thread();

DirectionAnalyzer directionAnalyzer = DirectionAnalyzer();
WifiConnector wifiConnector = WifiConnector();

void threadTask() {

  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIGGER, LOW);
  durationTwo = pulseIn(ECHO, HIGH);
  distanceTwo = (durationTwo/2) / 29.1;
}

void threadTaskTwo() {

  digitalWrite(TRIGGER2, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIGGER2, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIGGER2, LOW);
  durationOne = pulseIn(ECHO2, HIGH);
  distanceOne = (durationOne/2) / 29.1;
}

void setup() {

  Serial.begin (9600);
  pinMode(TRIGGER2, OUTPUT);
  pinMode(ECHO2, INPUT);
  pinMode(SPEAKER, OUTPUT);
  connected = false;
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  threadOne.onRun(threadTask);
  threadOne.setInterval(200);
  threadTwo.onRun(threadTaskTwo);
  threadTwo.setInterval(200);
  delay(100);
}

void loop() {

  if(connected == false) {
      wifiConnector.initializeConnection();
      connected = true;
  }


  threadTask();
  threadTaskTwo();
  Serial.println(distanceOne);
  Serial.println(distanceTwo);
  directionAnalyzer.captureValue(distanceOne, 1);
  directionAnalyzer.captureValue(distanceTwo, 2);
  directionAnalyzer.analyzeDirection();
  int dir = directionAnalyzer.getDirection();
  switch (dir) {
    case 1:
    Serial.println("LEFT");
    digitalWrite(SPEAKER, HIGH);
    delay(50);
    digitalWrite(SPEAKER, LOW);
    wifiConnector.sendRequest("/api/parking/decrement/");
    break;
    case 2:
    Serial.println("RIGHT");
    digitalWrite(SPEAKER, HIGH);
    delay(300);
    digitalWrite(SPEAKER, LOW);
    wifiConnector.sendRequest("/api/parking/increment/");

    break;
  }

  delay(50);
}
