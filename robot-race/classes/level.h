#pragma once
#include <iostream>
#include <iterator>
#include <list>

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
    std::list<std::string> moveList;

  public:
    static int matrixWidth; 
    static int matrixHeight;
    static int endCoordX; 
    static int endCoordY;
    Field();
    Field(char newSymbol, int x_coord, int y_coord);
    Field(Field& secondObj);
    //~Field();
  
    void swapObj(Field& a);
    //swapping _ with a new robot symbol
    void createRobot(char robotSymbol); 
    bool getIsEmpty();
    bool getIsEnd();
    bool getIsWall();
    bool getIsRobot();
    //returning symbol from these coords
    char getSymbol();
    //robot becomes empty field - used when robot comes to end
    void beEmpty();
    //stores old move strings to end of moveList
    void storeMove(std::string move);
    //prints all old moves
    void replayGame();

};

