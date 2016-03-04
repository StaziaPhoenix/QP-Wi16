#ifndef grid_h
#define grid_h

#include "Arduino.h"
#include "controller.h"


class grid
{
  public:
    grid(int col, int dlay);
    void setData(int moveMode);
    int adjustData(int i, int moveMode);
    int getData(int i);
    int left(int row, int col);
    int right();
    int up();
    int down();
  private:
    int numCol;
    int delay;
    int colInit[];
    int colData[];
};
#endif 

