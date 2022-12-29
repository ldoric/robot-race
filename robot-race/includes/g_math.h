#pragma once

#include <iostream>

namespace gm{

  int add(int, int); //takes in 2 ints and return their sum in int type
  double add(double, double); //takes in 2 doubles and return their sum in double type

  int sub(int, int);  //takes in 2 ints and returns their subtraction (first - second) in int type
  double sub(double, double); //takes in 2 doubles and returns their subtraction (first - second) in double type

  int multi(int, int); //takes in 2 ints and return their product in int type
  double multi(double, double); //takes in 2 doubles and return their product in double type

  int div(int, int); //takes in 2 ints and return their division floored in int type
  double div(double, double); //takes in 2 doubles and return their division in double type

  double power(int, double); //takes in 1 int as base and 1 double as the power and returns base^power as a double
  double power(double, double); //takes in 2 double as base and power and returns base^power as a double

  double sqroot(int); //takes in 1 int and returns square root of it as a double
  double sqroot(double); //takes in 1 double and returns square root of it as a double
}