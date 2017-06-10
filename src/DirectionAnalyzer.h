#ifndef DIRECTIONANALYZER_H
#define DIRECTIONANALYZER_H

const int MAX_DISTANCE = 150;
const int MIN_DISTANCE = 5;

struct car_state {
  bool left;
  bool right;
} ;

struct sensor_values {
  int left;
  int right;
} ;

class DirectionAnalyzer {

private:
  car_state state;
  car_state lastState;
  car_state firstState;
  sensor_values sensorValues;
  int direction;

public:
  DirectionAnalyzer();
  void captureValue(int value, int thread);
  void analyzeDirection();
  int getDirection();
};

#endif
 