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
#define MEMORY_ALLOC_ERROR (-1)

//function declarations
int txtToString(std::string fileName, std::string& data);
int levelToMatrix(std::string levelStr, char** matrix);
int getLevelSize(const std::string levelStr, int& width, int& height);
int getMatrixSize(const std::string levelStr, int& matW, int& matH);
int createMatrix(char** matrix, int matW, int matH);


int main()
{
  std::string data;
  char** lvlMatrix = nullptr;
  int matW = 0, matH = 0;
  int check_msg = 0;

  txtToString("data/lvl1.txt", data);

  std::cout<<data<<std::endl;
  std::cout<<gs::strLen(data) << std::endl;

  

  getMatrixSize(data, matW, matH);
  check_msg = createMatrix(lvlMatrix, matW, matH);
  if(check_msg = NULL)
  {
    std::cout<<"Memory failed to allocate" << std::endl;
    return MEMORY_ALLOC_ERROR;
  }

  std::cout<< data[1][1] << std::endl;
  //levelToMatrix(data, lvlMatrix);
   
  return 0;
}


int levelToMatrix(const std::string levelStr, char** matrix)
{
  int strW = 0, strH = 0;
  getLevelSize(levelStr, strW, strH);

  

  // for(int i = 0; i < strW; i = i + 2)
  // {
  //   for(int j = 0; i )

  // }


  return SUCCESS;
}


int createMatrix(char** matrix, int matW, int matH)
{
  matrix = new char*[matH];
  for (int i = 0; i<matH; ++i)
  {
    matrix[i] = new char[matW];
  }

  if (matrix == nullptr){
    return MEMORY_ALLOC_ERROR;
  }

  return SUCCESS;

}


int getMatrixSize(const std::string levelStr, int& matW, int& matH)
{
  int a = 0, b = 0;
  getLevelSize(levelStr, a, b);

  matW = a/2;
  matH = b;

  return SUCCESS;
}


int getLevelSize(const std::string levelStr, int& width, int& height)
{
  width = 0;
  int lenghtOfStr = gs::strLen(levelStr);

  while(levelStr[width] != '\n')
  {
    width++;
  }

  width = width + 1;
  height = lenghtOfStr / width;

  return SUCCESS;
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