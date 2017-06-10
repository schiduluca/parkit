#ifndef DIRECTIONANALYZER_H
#define DIRECTIONANALYZER_H

const int MAX_DISTANCE = 60;
const int MIN_DISTANCE = 5;

struct car_state {
  bool left;
  bool right;
} ;

struct sensor_values {
  int left;
  int right;
} ;

// const int IN_CENTRE = 5;
// const int LEFT_RIGHT = 4;
// const int LEFT_LEFT = 3;
// const int CAME_FROM_RIGHT = 2;
// const int CAME_FROM_LEFT = 1;
// const int NULL_POSITION = 0;

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
 