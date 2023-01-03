#include <iostream>
#include "classes/level.h"

Field::Field()
{
  symbol = ' ';
  isEnd = false;
  isEmpty = true;
}

Field::Field(char newSymbol)
{
  symbol = newSymbol;
  std::cout<<"radi";
  
  if(symbol == '$'){
    isEnd = true;
  }
  else{
    isEnd = false;
  }

  isEmpty = false;
}

  Field::Field(Field& secondObj)
  {
    symbol = secondObj.symbol;
    isEnd = secondObj.isEnd;
    isEmpty = secondObj.isEmpty;
  }

//Field::~Field(){;}

//*used for mainloop for swapping current symbols
void Field::swapObj(Field& a, Field& b)
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

char Field::getSymbol()
{
  return symbol;
}

void Field::setSymbol(char newSymbol) //used for adding robots to lvl after loading it (not used in mainloop)
{
  //*only able to change symbol if inserting a robot
  for(auto name : robotNames)
  {
    if (newSymbol == name)
    {
      symbol = newSymbol;
      break;
    }

  }
  //for testing, remove/change after 
  if (newSymbol != symbol)
  {
      std::cout<<"Not able to change the symbol!" << std::endl;
  }
  
}    

