#pragma once
#include <iostream>
#include <iterator>
#include <list>


const char robotSymbols[4] = {'A', 'B', 'C', 'D'};

class Robots{

  private:
    char symbol;
    bool isAtEnd;
    int moves;
    std::list<int*> oldCoords;
    std::list<int*> knownWalls;   

  public:
    int coords[2];
    Robots();
    Robots(char newSymbol, int x_coord, int y_coord);
    Robots(Robots& secondObj);
    //sets new coords and logs old ones in a list (first coord = first in the list)
    void newCoords(int x_coord, int y_coord);
    //can be used(edited version) in robot moving position because its not used when robot is created
    void setRobot(char newSymbol, int x_coord, int y_coord);
    //printing symbol and coords 
    void printInfo();
    //printing movment history
    void printMovmentHistory();
    //adding wall in knownWall list
    void foundNewWall(int x_coord, int y_coord);
    //changes isAtEnd to true
    void setAtEnd();
    //returns true if at end
    bool getIsAtEnd();
    //returns num of moves
    int getMoves();


};


