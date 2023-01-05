#include <iostream>

namespace gl
{
  void displayMessage(std::string message)
  {
    std::cout << message << std::endl;
  }

  void displayMessageInt(std::string message, int num)
  {
    std::cout << message << num << std::endl;
  }

  void displayMessageFloat(std::string message, float num)
  {
    std::cout << message << num << std::endl;
  }

  void displayMessageChar(std::string message, char x)
  {
    std::cout << message << x << std::endl;
  }
}