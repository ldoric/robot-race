#pragma once
#include <iostream>

//*__________________
/* same as robotNames, couldnt figure out how to declare this
only once as it gives an error because we include both header
files in main */ 
//*_________________
const char robotSymbols[4] = {'A', 'B', 'C', 'D'};

class Robots{

  private:
    char symbol;
    int coords[2];

  public:
    Robots();
    Robots(char newSymbol, int x_coord, int y_coord);
    Robots(Robots& secondObj);
    void setRobot(char newSymbol, int x_coord, int y_coord);
    //can be used(edited version) in robot moving position because its not used when robot is created 
    void printInfo();
    //printing symbol and coords

};
