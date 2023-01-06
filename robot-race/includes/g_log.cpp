#include <iostream>

namespace gl
{
  void displayMessage(std::string message)
  {
    std::cout << message << std::endl;
  }

  void displayMessageInt(std::string message, int number)
  {
    std::cout << message << number << std::endl;
  }

  void displayMessageFloat(std::string message, double number)
  {
    std::cout << message << number << std::endl;
  }

  void displayMessageChar(std::string message, char sign)
  {
    std::cout << message << sign << std::endl;
  }
}