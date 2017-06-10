#include "DirectionAnalyzer.h"

DirectionAnalyzer::DirectionAnalyzer() {
  state.left = false;
  state.right = false;
  lastState.left = false;
  lastState.right = false;
  firstState.left = false;
  firstState.right = false;
  direction = 0;
}

int DirectionAnalyzer::getDirection() {
  return direction;
}


void DirectionAnalyzer::analyzeDirection() {
  if (lastState.left && lastState.right && !state.left && state.right) {
    direction = 2;
  } else if (lastState.left && lastState.right && state.left && !state.right) {
    direction = 1;
  } else {
    direction = 0;
  }
}

void DirectionAnalyzer::captureValue(int value, int thread) {
  switch (thread) {
    case 1:
      sensorValues.left = value;
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
