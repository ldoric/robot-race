#pragma once

#include<iostream>

namespace gs{

  int strComp(std::string, std::string); // takes in 2 strings and returns: 1 - first bigger, -1 - second bigger, 0 - equal

  int strLen(std::string);  // takes in 1 string and returns its length as an int

  std::string strRev(std::string); // takes in 1 string and returns it reversed, it doesn't modify the first string

  void strCopy(std::string, std::string); // takes in two strings and copies second into the first, returns nothing

}