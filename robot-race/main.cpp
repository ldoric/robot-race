//standard lib
#include <iostream>
#include <fstream>
#include <sstream>

//gmaz lib
#include "includes/g_math.h"
#include "includes/g_string.h"

//constants
#define FILE_READ_ERROR (-1)
#define SUCCESS (0)

//function declarations
int txtToString(std::string fileName, std::string& data);


int main()
{
  // std::string data;
  // txtToString("data/lvl1.txt", data);

  // std::cout<<data<<std::endl;

  return 0;
}


int txtToString(std::string fileName, std::string& data)
{
  std::ifstream ip;
  ip.open(fileName);

  if (ip.fail()){
    std::cout<<"Fail failed to open!" << std::endl;
    return FILE_READ_ERROR;
  }

  std::stringstream buffer;
  buffer << ip.rdbuf();

  data = buffer.str();


  ip.close();
  return SUCCESS;
}