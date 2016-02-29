#include "grid.h"
grid::grid(int col)
{
  numCol = col; 
  col[numCol];
  colInit[numCol]; 
  for (int i =0; i < numCol; i++)
  {
    col[i] = 0;
  }
  for (int i = 0; i < numCol; i++)
  {
    colInit[i] = 0xFF;
  }
}
void grid::defState()
{
  
}


