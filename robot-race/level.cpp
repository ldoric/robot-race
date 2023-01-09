#include <iostream>
#include "classes/level.h"




Field::Field()
{
  symbol = '?';
  isEnd = false;
  isEmpty = false;
  isRobot = false;
  isWall = false;
  noSymbol = true;

  coords[0] = 0, coords[1] = 1;
}

Field::Field(char newSymbol, int x_coord, int y_coord)
{
  coords[0] = x_coord;
  coords[1] = y_coord;

  symbol = newSymbol;

  if (symbol == '$')
  {
    isEnd = true;
  }
  else
  {
    isEnd = false;
  }

  if (symbol == '#')
  {
    isWall = true;
  }
  else
  {
    isWall = false;
  }

  isRobot = false;
  for(auto name : robotNames)
  {
    if(symbol == name)
    {
      isRobot = true;
    }
  }

  if(symbol == '_')
  {
    isEmpty = true;
  }
  else
  {
    isEmpty = false;
  }

  noSymbol = false;
}

Field::Field(Field &secondObj)
{
  symbol = secondObj.symbol;
  isEnd = secondObj.isEnd;
  isEmpty = secondObj.isEmpty;
  isRobot = secondObj.isRobot;
  isWall = secondObj.isWall;
  
  coords[0] = secondObj.coords[0];
  coords[1] = secondObj.coords[1];
}

// Field::~Field(){;}

//*used in mainloop for swapping current symbols
void Field::swapObj(Field &a, Field &b)
{
  Field temp = a;
  a = b;
  b = temp;
}

bool Field::getIsEmpty()
{
  return isEmpty;
}

bool Field::getIsEnd()
{
  return isEnd;
}

bool Field::getIsWall()
{
  return isWall;
}

bool Field::getIsRobot()
{
  return isRobot;
}

char Field::getSymbol()
{
  return symbol;
}

void Field::createRobot(char robotSymbol)
{
  //*only able to change symbol if inserting a robot
  if(isEmpty)
  {
    for (auto name : robotNames)
    {
      if (robotSymbol == name)
      {
        symbol = robotSymbol;
        isRobot = true;
        isEmpty = false;
        break;
      }
    }
  }
  //?*idk what is the real use of this
  // for testing, remove/change after
  /*
  if (newSymbol != symbol)
  {
    std::cout << "Not able to change the symbol!" << std::endl;
  }
  */
}

