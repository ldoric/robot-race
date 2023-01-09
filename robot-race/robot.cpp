#include <iostream>
#include "classes/robot.h"

Robot::Robot()
{
  symbol = '?';

  coords[0] = 0, coords[1] = 1;
}

Robot::Robot(char newSymbol, int x_coord, int y_coord)
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

Robot::Robot(Robot &secondObj)
{
  symbol = secondObj.symbol;
  coords[0] = secondObj.coords[0];
  coords[1] = secondObj.coords[1];
}