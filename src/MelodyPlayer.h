#ifndef MELODY_H
#define MELODY_H

class MelodyPlayer {

private:
  int buzzerPin;

public:
  MelodyPlayer(int buzzerPin);
  void PlayWelcome();
  void PlayGoodbye();
};

#endif
 