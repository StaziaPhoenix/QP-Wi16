#ifndef grid_h
#define grid_h

class grid
{
  public:
    grid(int col);
    void defState();
    void setup(); 
    void setData(); 
  private:
    int numCol;
    int delay;
    char col[];
    char colInit[];
    char col0, col1, col2, col4;
    void adjustData(int i);
    
};
#endif 

