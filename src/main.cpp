#include <Arduino.h>
#include <Thread.h>
#include <ThreadController.h>
#include "DirectionAnalyzer.h"
#include <SPI.h>
#include "WifiConnector.h"
#include "MelodyPlayer.h"

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

long getDistance(int trigger, int echo) {

  digitalWrite(trigger, LOW);
  delayMicroseconds(2);

  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigger, LOW);
  int duration = (int)pulseIn(echo, HIGH);
  int distance = (int)(duration/2) / 29.1;

  return distance;
}

void setup() {

  Serial.begin (9600);
  pinMode(TRIGGER2, OUTPUT);
  pinMode(ECHO2, INPUT);
  pinMode(SPEAKER, OUTPUT);
  connected = false;
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  delay(100);
}

void loop() {

  if(connected == false) {
      wifiConnector.initializeConnection();
      connected = true;
  }

  distanceOne = getDistance(TRIGGER, ECHO);
  distanceTwo = getDistance(TRIGGER2, ECHO2);
  Serial.println(distanceOne);
  Serial.println(distanceTwo);
  directionAnalyzer.captureValue(distanceOne, 1);
  directionAnalyzer.captureValue(distanceTwo, 2);
  directionAnalyzer.analyzeDirection();
  int dir = directionAnalyzer.getDirection();
  switch (dir) {
    case 2:
    Serial.println("LEFT");
    digitalWrite(SPEAKER, HIGH);
    delay(2000);
    digitalWrite(SPEAKER, LOW);
    wifiConnector.sendRequest("/api/parking/decrement/");
    break;
    case 1:
    Serial.println("RIGHT");
    digitalWrite(SPEAKER, HIGH);
    delay(1000);
    digitalWrite(SPEAKER, LOW);
    delay(1000);    
    wifiConnector.sendRequest("/api/parking/increment/");

    break;
  }

  delay(50);
}
