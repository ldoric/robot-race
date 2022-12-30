#include <iostream>

namespace gs
{

  // takes in 1 string and returns its length as an int
  int strLen(std::string str)
  {
    int i = 0;
    while (str[i] != '\0')
    {
      i++;
    }

    return i;
  }

  // takes in 2 strings and returns: 1 - first bigger, -1 - second bigger, 0 - equal
  int strComp(std::string first, std::string second)
  {
    if (strLen(first) == strLen(second))
    {
      int i = 0;

      while ((first[i] == second[i]))
      {
        i++;

        if (i == strLen(first))
        {
          return 0;
        }
      }

      if (first[i] > second[i])
      {
        return 1;
      }
      else if (second[i] > first[i])
      {
        return -1;
      }
      else
      {
        std::cout << "This shouldn't happen!" << std::endl;
        return -69;
      }
    }
    else if (strLen(first) > strLen(second))
    {
      return 1;
    }
    else
    {
      return -1;
    }
  }

  // takes in 1 string and returns it reversed, it doesn't modify the first string
  std::string strRev(std::string str)
  {
    int len = strLen(str);
    std::string reversed = str;

    reverse(reversed.begin(), reversed.end());

    return reversed;
  }

  // takes in two strings and copies second into the first, returns nothing
  void strCopy(std::string destination, std::string source)
  {
    destination = source;
  }

}