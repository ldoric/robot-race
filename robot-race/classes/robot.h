#pragma once
#include <iostream>
#include <iterator>
#include <list>


const char robotSymbols[4] = {'A', 'B', 'C', 'D'};

class Robots{

  private:
    char symbol;
    std::list<int*> oldCoords;
    std::list<int*> knownWalls;   

  public:
    int coords[2];
    Robots();
    Robots(char newSymbol, int x_coord, int y_coord);
    Robots(Robots& secondObj);
    void newCoords(int x_coord, int y_coord);
    //sets new coords and logs old ones in a list (first coord = first in the list)
    void setRobot(char newSymbol, int x_coord, int y_coord);
    //can be used(edited version) in robot moving position because its not used when robot is created 
    void printInfo();
    //printing symbol and coords
    void printMovmentHistory();
    //printing movment history
    void foundNewWall(int x_coord, int y_coord);
    //adding wall in knownWall list

};


