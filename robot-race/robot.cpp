#include <iostream>
#include "classes/robot.h"

Robots::Robots()
{
  symbol = '?';

  coords[0] = -2, coords[1] = -2;
}

Robots::Robots(char newSymbol, int x_coord, int y_coord)
{
  coords[0] = x_coord;
  coords[1] = y_coord;
  symbol = '?';

  for (auto symb : robotSymbols)
  {
    if (newSymbol == symb )
    {
      symbol = newSymbol;
      break;  
    }
  }  
}

Robots::Robots(Robots &secondObj)
{
  symbol = secondObj.symbol;
  coords[0] = secondObj.coords[0];
  coords[1] = secondObj.coords[1];
}

void Robots::newCoords(int x_coord, int y_coord)
{
  int *temp = new int(2);
  temp[0] = coords[0];
  temp[1] = coords[1];

  oldCoords.push_back(temp);
  coords[0] = x_coord;
  coords[1] = y_coord;
}

void Robots::foundNewWall(int x_coord, int y_coord)
{
  int *temp = new int(2);
  temp[0] = x_coord;
  temp[1] = y_coord;

  knownWalls.push_back(temp);
}

void Robots::printMovmentHistory()
{ 

  std::cout << "Movment History:" << std::endl;

  for (auto it = oldCoords.begin(); it != oldCoords.end(); ++it)
  {
    std::cout << "\t=> " << (*it)[0] << "-" << (*it)[1] << std::endl;
  }
  std::cout << "\n";
  
}

void Robots::setRobot(char newSymbol, int x_coord, int y_coord)
{
  coords[0] = x_coord;
  coords[1] = y_coord;

  std::cout << newSymbol << std::endl;

  for (auto symb : robotSymbols)
  {
    if (newSymbol == symb )
    {
      symbol = newSymbol;
      break;  
    }
  }  
}

void Robots::printInfo()
{
  std::cout<< "symbol: " << symbol << ", coords: " << coords[0] << " " << coords[1] << std::endl;
}