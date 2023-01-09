#pragma once
#include <iostream>

const char robotNames[4] = {'A', 'B', 'C', 'D'};

class Field
{

  private:
    char symbol;
    bool isEnd; // if true, symbol == '$'
    bool isEmpty; // if true, symbol == '_'
    bool isRobot; // if true, symbol == 'A', 'B', 'C', 'D'
    bool isWall; // if true, symbol == '#'
    bool noSymbol;
    int coords[2]; // x = coords[0], y = cords[1]

  public:
    static int matrixWidth; //myb this should be const?
    static int matrixHeight;
    Field();
    Field(char newSymbol, int x_coord, int y_coord);
    Field(Field& secondObj);
    //~Field();
  
    void swapObj(Field& a, Field& b);
    void createRobot(char robotSymbol);
    bool getIsEmpty();
    bool getIsEnd();
    bool getIsWall();
    bool getIsRobot();
    char getSymbol();

};

