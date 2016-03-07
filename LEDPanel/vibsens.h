#ifndef vibsens_h
#define vibsens_h
#include "stdlib.h"

class vibsens
{
  public: 
    vibsens(int pin);
    void slowFreq();
    int checkSens();
    int rawRead();
    int vibrateRand();
    
  private: 
    int _pin; 
};
#endif

