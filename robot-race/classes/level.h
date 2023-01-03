#pragma once
#include <iostream>


//myb use enum
const char robotNames[4] = {'A', 'B', 'C', 'D'};

class Field{

  private:
    char symbol;
    bool isEnd;
    bool isEmpty;

  public:
    Field();
    Field(char newSymbol);
    Field(Field& secondObj);
    //~Field();
  
    void swapObj(Field& a, Field& b);
    bool getIsEmpty();
    bool getIsEnd();
    char getSymbol();
    void setSymbol(char newSymbol);

};

