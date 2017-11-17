#ifndef controller_h
#define controller_h 

class controller 
{

  public:
    controller(int x, int y, int z);

    //all possible move directions 
    int moveLeft();
    int moveRight();
    int moveUp();
    int moveDown();
    int moveUL();
    int moveUR();
    int moveDL();
    int moveDR();
    int zMode(); 

  private:
    int xPin;
    int yPin;
    int zPin;
};
#endif 
