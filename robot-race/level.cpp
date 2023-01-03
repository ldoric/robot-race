#include <iostream>

//available robots
const char robotNames[4] = {'A', 'B', 'C', 'D'};

class Field{

  private:
    char symbol;
    bool isEnd;
    bool isEmpty;


  public:
    Field()
    {
      symbol = ' ';
      isEnd = false;
      isEmpty = true;
    }

    Field(char newSymbol)
    {
      symbol = newSymbol;
      
      if(symbol == '$'){
        isEnd = true;
      }
      else{
        isEnd = false;
      }

      isEmpty = false;
    }

     Field(Field& secondObj)
     {
       symbol = secondObj.symbol;
       isEnd = secondObj.isEnd;
       isEmpty = secondObj.isEmpty;
     }

    //~Field(){;}

    //*used for mainloop for swapping current symbols
    void swapObj(Field& a, Field& b)
    {
      Field temp = a;
      a = b;
      b = temp;
    }

    bool getIsEmpty()
    {
      return isEmpty;
    }

    bool getIsEnd()
    {
      return isEnd;
    }

    char getSymbol()
    {
      return symbol;
    }

     void setSymbol(char newSymbol) //used for adding robots to lvl after loading it (not used in mainloop)
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

};