#ifndef DIRECTIONANALYZE_H
#define DIRECTIONANALYZER_H

class DirectionAnalyzer {

private:
  int direction;
  int valuesOne[2];
  int valuesTwo[2];

public:
  DirectionAnalyzer();
  void captureValue(int value, int thread);
  void analyzeDirection();
  int getDirection();
};

#endif
