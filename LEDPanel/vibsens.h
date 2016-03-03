#ifndef vibsens_h
#define vibsens_h

class vibsens
{
  public: 
    vibsens(int pin);
    void slowFreq();
  private: 
    int _pin; 
};
#endif

