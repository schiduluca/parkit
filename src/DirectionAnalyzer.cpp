#include "DirectionAnalyzer.h"

DirectionAnalyzer::DirectionAnalyzer() {
  for(int i = 0; i < 2; i++) {
    valuesOne[i] = -1;
    valuesTwo[i] = -1;
  }
}

int DirectionAnalyzer::getDirection() {
  return this->direction;
}


void DirectionAnalyzer::analyzeDirection() {
  if(valuesOne[0] + 20 < valuesOne[1] && direction == 0) {
    direction = 1; //LEFT
  } else

  if(valuesTwo[0] + 20 < valuesTwo[1] && direction == 0) {
    direction = 2; //RIGHT
  } else {
    direction = 0;
  }
}

void DirectionAnalyzer::captureValue(int value, int thread) {
  switch (thread) {
    case 1:
      valuesOne[1] = valuesOne[0];
      valuesOne[0] = value;
    break;
    case 2:
      valuesTwo[1] = valuesTwo[0];
      valuesTwo[0] = value;
    break;
  }
}
