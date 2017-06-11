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


Thread thread = Thread();

DirectionAnalyzer directionAnalyzer = DirectionAnalyzer();
WifiConnector wifiConnector = WifiConnector();

long getDistance(int trigger, int echo) {

  digitalWrite(trigger, LOW);
  delayMicroseconds(2);

  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigger, LOW);
  int duration = (int)pulseIn(echo, HIGH);
  int distance = (int)(duration*0.034/2);

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
  delayMicroseconds(50);
  distanceTwo = getDistance(TRIGGER2, ECHO2);

  Serial.print(distanceOne);
  Serial.print("\t");   
  Serial.print(distanceTwo);

  directionAnalyzer.captureValue(distanceOne, 1);
  directionAnalyzer.captureValue(distanceTwo, 2);
  directionAnalyzer.analyzeDirection();

  Serial.print("\t");   
  Serial.print(directionAnalyzer.getLeftProgress());
  Serial.print("\t");   
  Serial.print(directionAnalyzer.getRightProgress());

  int dir = directionAnalyzer.getDirection();
  switch (dir) {
    case 2:
    directionAnalyzer.resetProgress();
    Serial.println("LEFT");
    digitalWrite(SPEAKER, HIGH);
    delay(200);
    digitalWrite(SPEAKER, LOW);
    wifiConnector.sendRequest("/api/parking/decrement/");
    break;
    case 1:
    directionAnalyzer.resetProgress();
    Serial.println("RIGHT");
    digitalWrite(SPEAKER, HIGH);
    delay(100);
    digitalWrite(SPEAKER, LOW);
    delay(100);    
    wifiConnector.sendRequest("/api/parking/increment/");

    break;
  }

  Serial.println();
  delay(10);
}
