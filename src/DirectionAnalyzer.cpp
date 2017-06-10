#include "DirectionAnalyzer.h"

DirectionAnalyzer::DirectionAnalyzer() {
  for(int i = 0; i < 2; i++) {
    valuesOne[i] = -1;
    valuesTwo[i] = -1;
  }
  state.left = false;
  state.right = false;
  lastState.left = false;
  lastState.right = false;
}

int DirectionAnalyzer::getDirection() {
  return this->direction;
}


void DirectionAnalyzer::analyzeDirection() {
  if (lastState.left && lastState.right && !state.left && state.right) {
    direction = 2;
  } else if (lastState.left && lastState.right && state.left && !state.right) {
    direction = 1;
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
