#include "DirectionAnalyzer.h"

DirectionAnalyzer::DirectionAnalyzer() {
  state.left = false;
  state.right = false;
  lastState.left = false;
  lastState.right = false;
  firstState.left = false;
  firstState.right = false;
  direction = 0;
  leftProgress = 0;
  rightProgress = 0;
}

int DirectionAnalyzer::getDirection() {
  return direction;
}

int DirectionAnalyzer::getLeftProgress() {
  return leftProgress;
}

int DirectionAnalyzer::getRightProgress() {
  return rightProgress;
}

void DirectionAnalyzer::resetProgress() {
  leftProgress = 0;
  rightProgress = 0;
}

void DirectionAnalyzer::analyzeDirection() {
  if (leftProgress < 5 &&
    lastState.left == LEFT_PATTERN[0][leftProgress] && lastState.right == LEFT_PATTERN[1][leftProgress] &&   
    state.left == LEFT_PATTERN[0][leftProgress + 1] && state.right == LEFT_PATTERN[1][leftProgress + 1] 
  ) {
    leftProgress++;
  } else if (leftProgress > 0 &&
    lastState.left == LEFT_PATTERN[0][leftProgress] && lastState.right == LEFT_PATTERN[1][leftProgress] &&   
    state.left == LEFT_PATTERN[0][leftProgress - 1] && state.right == LEFT_PATTERN[1][leftProgress - 1] 
  ) {
    leftProgress--;
  } else if (!(state.left == LEFT_PATTERN[0][leftProgress] && state.right == LEFT_PATTERN[1][leftProgress])) {
    leftProgress = 0;
  }

  if (rightProgress < 5 &&
    lastState.left == RIGHT_PATTERN[0][rightProgress] && lastState.right == RIGHT_PATTERN[1][rightProgress] &&   
    state.left == RIGHT_PATTERN[0][rightProgress + 1] && state.right == RIGHT_PATTERN[1][rightProgress + 1] 
  ) {
    rightProgress++;
  } else if (rightProgress > 0 &&
    lastState.left == RIGHT_PATTERN[0][rightProgress] && lastState.right == RIGHT_PATTERN[1][rightProgress] &&   
    state.left == RIGHT_PATTERN[0][rightProgress - 1] && state.right == RIGHT_PATTERN[1][rightProgress - 1] 
  ) {
    rightProgress--;
  } else if (!(state.left == RIGHT_PATTERN[0][rightProgress] && state.right == RIGHT_PATTERN[1][rightProgress])) {
    rightProgress = 0;
  }

  if (leftProgress == 4) {
    direction = LEFT;
  } else if (rightProgress == 4) {
    direction = RIGHT;
  } else {
    direction = 0;
  }

  // if (lastState.left && lastState.right && !state.left && state.right) {
  //   direction = LEFT;
  // } else if (lastState.left && lastState.right && state.left && !state.right) {
  //   direction = RIGHT;
  // } else {
  //   direction = 0;
  // }
}

void DirectionAnalyzer::captureValue(int value, int thread) {
  switch (thread) {
    case 1:
      sensorValues.right = value;
      if (value < MAX_DISTANCE && value > MIN_DISTANCE) {
        lastState.left = state.left;
        state.left = true;
      } else {
        lastState.left = state.left;
        state.left = false;
      }
    break;
    case 2:
      sensorValues.right = value;
      if (value < MAX_DISTANCE && value > MIN_DISTANCE) {
        lastState.right = state.right;
        state.right = true;
      } else {
        lastState.right = state.right;
        state.right = false;
      }
    break;
  }
}
