#include <iostream>
#include "classes/level.h"
#include <Windows.h>


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
void Field::swapObj(Field &a)
{
  Field temp = *this;
  *this = a;
  a = temp;
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

void Field::beEmpty()
{
  symbol = '_';
  isRobot = false;
  isEmpty = true;
}

void Field::storeMove(std::string move)
{
  moveList.push_back(move);
}

void Field::replayGame()
{
  int i=1; //counter for what move
  std::cout << "\nGame Replay(press enter for next move):\n" << std::endl;

  for (auto it = moveList.begin(); it != moveList.end(); ++it)
  {
    std::cout << "Move: " << i++ << ":\n" << std::endl;
    std::cout << *it << std::endl;
    std::cin.get();
  }
  std::cout << "\n";
}

int Field::matrixWidth = 0;
int Field::matrixHeight = 0;
int Field::endCoordX = 0;
int Field::endCoordY = 0;

