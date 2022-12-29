#include <iostream>
#include <cmath>

namespace gm
{

  int add(int first, int second)
  {
    return first + second;
  }

  double add(double first, double second)
  {
    return first + second;
  }

  int sub(int first, int second)
  {
    return first - second;
  }

  double sub(double first, double second)
  {
    return first - second;
  }

  int multi(int first, int second)
  {
    return first * second;
  }

  double multi(double first, double second)
  {
    return first * second;
  }

  int div(int first, int second)
  {
    if (NULL == second)
    {
      return -1;
    }
    return first / second;
  }

  double div(double first, double second)
  {
    if (NULL == second)
    {
      return -1;
    }
    return first / second;
  }

  double power(int base, double power)
  {
    return pow(base, power);
  }

  double power(double base, double power)
  {
    return pow(base, power);
  }

  double sqroot(int number)
  {
    return sqrt(number);
  }

  double sqroot(double number)
  {
    return sqrt(number);
  }

}