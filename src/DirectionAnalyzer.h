#ifndef DIRECTIONANALYZER_H
#define DIRECTIONANALYZER_H

const int MAX_DISTANCE = 100;
const int MIN_DISTANCE = 5;
const int LEFT = 1;
const int RIGHT = 2;
const bool LEFT_PATTERN[2][5] = {
  {0, 0, 1, 1, 0},
  {0, 1, 1, 0, 0}
};
const bool RIGHT_PATTERN[2][5] = {
  {0, 1, 1, 0, 0},
  {0, 0, 1, 1, 0}
};

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
  int rightProgress;
  int leftProgress;
  car_state state;
  car_state lastState;
  car_state firstState;
  sensor_values sensorValues;
  int direction;

public:
  DirectionAnalyzer();
  void captureValue(int value, int thread);
  void analyzeDirection();
  void resetProgress();  
  int getDirection();
  int getLeftProgress();
  int getRightProgress();
};

#endif
 