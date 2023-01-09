#include <iostream>
#include "classes/robot.h"

Robots::Robots()
{
  symbol = '?';

  coords[0] = 0, coords[1] = 1;
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