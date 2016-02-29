#ifndef grid_h
#define grid_h

class grid
{
  public:
    grid(int col);
    void defState();
  private:
    int numCol;
    char col[];
    char colInit[];
    
};
#endif 

