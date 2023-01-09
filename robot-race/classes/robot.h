#pragma once
#include <iostream>

//*__________________
/* same as robotNames, couldnt figure out how to declare this
only once as it gives an error because we include both header
files in main */ 
//*_________________
const char robotSymbols[4] = {'A', 'B', 'C', 'D'};

class Robot{

  private:
    char symbol;
    int coords[2];

  public:
    Robot();
    Robot(char newSymbol, int x_coord, int y_coord);
    Robot(Robot& secondObj);

};
