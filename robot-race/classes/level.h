#pragma once
#include <iostream>


//myb use enum
const char robotNames[4] = {'A', 'B', 'C', 'D'};

class Field{

  private:
    char symbol;
    bool isEnd;
    bool isEmpty;
    bool isRobot;
    bool isWall;
    int coords[2];

  public:
    Field();
    Field(char newSymbol, int x_coord, int y_coord);
    Field(Field& secondObj);
    //~Field();
  
    void swapObj(Field& a, Field& b);
    bool getIsEmpty();
    bool getIsEnd();
    bool getIsWall();
    bool getIsRobot();
    char getSymbol();
    void setSymbol(char newSymbol);

};

