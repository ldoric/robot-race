//standard lib
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <iterator>
#include <list>
#include <cstdlib>
#include <Windows.h>


//gmaz lib
#include "includes/g_math.h"
#include "includes/g_string.h"
#include "includes/g_log.h"

//classes
#include "classes/level.h"
#include "classes/robot.h"

//constants
#define FILE_READ_ERROR (-1)
#define SUCCESS (0)
#define MEMORY_ALLOC_ERROR (-1)
#define MAX_ROBOTS (4)
#define SEARCH_FAIL (-1)
#define MAX_MOVES (80)

//function declarations
int levelLoad(std::string fileName, std::string& data);
int levelToMatrix(std::string levelStr, Field** matrix);
int getLevelSize(const std::string levelStr, int& width, int& height);
int getMatrixSize(const std::string levelStr, int& matW, int& matH);
//returns dynamically allocated 2D array of Field objects
Field** allocateMatrix(int matW, int matH);
//returns dynamically allocated 1D array of Robots objects
Robots* allocateRobots(int& robotNum);
int createMatrix(Field** matrix, int matW, int matH);
void displayLevel(Field** matrix);
void showLevelInfo(Field** matrix);
int generateRandomCoords(Field** matrix, Robots* robot, int couter, int& x_coord, int& y_coord);
//adds 1 robot in the already created matrix and creates a Robot object 
int addRobotToMatrix(Field** matrix, Robots* robot, int coord_x, int coord_y, int counter/*uses robotNames to get symbol*/); 
//calling addRobotToMatrix for each robot, manual or random coords
int createRobots(Field** matrix, Robots* robot, int robotNum);
//finds all 4 possible movements and checks wheather some of them are known wall, then calls moveRobot with one of directions
int prepareMove(Field** matrix, Robots* robot, int counter);
//if it's not wall, move robot - in matrix and robot class, also logging old coords
int moveRobot(Field** matrix, Robots* robot, int coord_x, int coord_y, int counter);
//calls prepareMove for each robot
int moveRobots(Field** matrix, Robots* robot, int robotNum);
//mainloop function
int mainLoop(Field** matrix, Robots* robot, int robotNum);
//gets the distance between coord and end coords
int getDistanceToEnd(Field** matrix, int x, int y);
//gets the distance between coord and robot coords
int getDistanceToRobot(Field** matrix, int x, int y, int robot_x, int robot_y);
//print in how manny move robots reached the end 
int showResults(Robots* robot, int RobotNum);
//printing every move once again
int showReplay(Field** matrix);

int main()
{
  std::string data;
  std::string levelName;
  Field** lvlMatrix = nullptr;
  Robots* Robot = nullptr;
  int matW = 0, matH = 0;
  int check_msg = 0;
  int robotNum = 0;
 
  gl::displayMessage("Enter level name (txt file): ");
  std::cin>>levelName;

  check_msg = levelLoad("data/" + levelName, data);

  if(check_msg != SUCCESS){
    gl::displayMessage("Level failed to load, check your input!");
    return FILE_READ_ERROR;
  }

  //getting level size
  getMatrixSize(data, matW, matH);

  //allocating memory
  lvlMatrix = allocateMatrix(matW, matH);
  Robot = allocateRobots(robotNum);

  //loading level into matrix
  levelToMatrix(data, lvlMatrix);
  gl::displayMessage("Printing the matrix after loading the level into it");
  displayLevel(lvlMatrix);
  showLevelInfo(lvlMatrix);

  //creating robots
  createRobots(lvlMatrix, Robot, robotNum);
  gl::displayMessage("Printing the matrix after loading robots in it");
  displayLevel(lvlMatrix);
  
  //Mainloop(to be implemented)
  gl::displayMessage("Mainloop:\n");

  //testing mainloop
  mainLoop(lvlMatrix, Robot, robotNum);

  showResults(Robot, robotNum);

  showReplay(lvlMatrix);
  

  return 0;
}


int mainLoop(Field** matrix, Robots* robot, int robotNum)
{
  bool allAtEnd; //if true after for loops -> return SUCCESS 

  for(int i = 0; i < MAX_MOVES; i++) //*only 80 moves for now and quits when any robot reaches $ (to be changed)
  {
    allAtEnd = true;
    gl::displayMessage("Move " + std::to_string(i+1) + ":\n");
    moveRobots(matrix, robot, robotNum);
    displayLevel(matrix);

    //check if any robot is on $ coords
    for(int j = 0; j < robotNum; j++)
    {
      if( !(robot[j].getIsAtEnd()) )
      {
        //add time delay for better visualisation
        Sleep(200);
        allAtEnd = false;
        break;
      }
    }

    if (!allAtEnd)
    {
      continue;
    }

    gl::displayMessage("All robots reached the end!!");
    return SUCCESS;
  }

  gl::displayMessage("Game Over - Max Moves reached!!");
  return SUCCESS;
}


int moveRobots(Field** matrix, Robots* robot, int robotNum)
{
  for(int i = 0; i < robotNum; i++)
  {
    if( !(robot[i].getIsAtEnd()) )
    {
      prepareMove(matrix, robot, i);
    }
  }
  return SUCCESS;
}


Robots* allocateRobots(int &robotNum)
{
  Robots* Robot = nullptr;

  while ((robotNum < 1) || (robotNum > MAX_ROBOTS))
  {
    gl::displayMessage("enter number of robots (max 4):");
    std::cin>> robotNum; 
  }
  Robot = new Robots[robotNum];
  
  if (Robot == nullptr)
  {
    gl::displayMessage("Memory failed to allocate - Robots");
  }
 
  gl::displayMessage("");

  return Robot;
}


Field** allocateMatrix(int matW, int matH)
{
  Field** lvlMatrix = nullptr;
  int check_msg = SUCCESS;
  lvlMatrix = new Field*[matW];

  for (int i = 0; i<matW; ++i)
  {
    lvlMatrix[i] = new Field[matH];

    if (lvlMatrix[i] == nullptr)
    {
      check_msg =  MEMORY_ALLOC_ERROR;
    }
  }

  if (lvlMatrix == nullptr)
  {
    check_msg = MEMORY_ALLOC_ERROR;
  }

  if(check_msg != SUCCESS)
  {
    gl::displayMessage("Memory failed to allocate - Field");
  }

  return lvlMatrix;
}


void showLevelInfo(Field** matrix)
{
  gl::displayMessage("Showing level info:");

  int width = Field::matrixWidth;
  int height = Field::matrixHeight;
  char curr_symbol;
  int count = 0;
  int inside_tiles = 0;
  int non_wall_tiles = 0;
  int inside_walls = 0;
  
  for(int j = 0; j < height; j++)
  {
    for(int i = 0; i < width; i++)
    {
      curr_symbol = matrix[i][j].getSymbol();
      for(auto robot : robotNames)
      {
        if(robot == curr_symbol)
        {
          count++;
        }
      }

      if((curr_symbol == '#') && (j != 0 && j != 5) && (i != 0 && i != 9))
      {
        inside_walls ++;
      }
    }
  }

  inside_tiles = (width*height) - (2*width + 2*height) + 4;
  non_wall_tiles = inside_tiles - inside_walls;

  std::cout<<"\t- Matrix size: " << width << " x " << height << std::endl;
  std::cout << "\t- Number of robots in level: " << count << std::endl;
  std::cout << "\t- Number of non-wall tiles: " << non_wall_tiles << std::endl;
  std::cout << std::endl;
}


void displayLevel(Field** matrix)
{
  std::string level = "";

  for(int j = 0; j < Field::matrixHeight; j++)
  {
    for(int i = 0; i <Field::matrixWidth; i++)
    {
      level +=  matrix[i][j].getSymbol();
    }
    level += "\n";
  }

  std::cout << level << std::endl;

  matrix[Field::endCoordX][Field::endCoordY].storeMove(level); //we store list in end obj

}


int levelToMatrix(const std::string levelStr, Field** matrix)
{
  int strW = 0, strH = 0;
  getLevelSize(levelStr, strW, strH);

  int a = -2;
  //inserting chars into matrix
  for(int j = 0; j < strH; j++)
  {
    for(int i = 0; i < strW; i+=2)
    {
      matrix[i/2][j] = Field(levelStr[a+=2], i/2, j);

      if (levelStr[a]=='$')
      {
        Field::endCoordX = i/2;
        Field::endCoordY = j;
      }

    }
  }

  Field::matrixWidth = strW/2;
  Field::matrixHeight = strH;

  return SUCCESS;
}


int createMatrix(Field** matrix, int matW, int matH)
{
  matrix = new Field*[matH];
  for (int i = 0; i<matH; ++i)
  {
    matrix[i] = new Field[matW];

    if (matrix[i] == nullptr)
    {
      return MEMORY_ALLOC_ERROR;
    }
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
  //gl::displayMessageInt("w: ", matW);
  //gl::displayMessageInt("h: ", matH);

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


int levelLoad(std::string fileName, std::string& data)
{
  std::ifstream ip;
  ip.open(fileName);

  if (ip.fail()){
    std::cout<<"File not found!" << std::endl;
    return FILE_READ_ERROR;
  }

  std::stringstream buffer;
  buffer << ip.rdbuf();

  data = buffer.str();


  ip.close();
  return SUCCESS;
}


int addRobotToMatrix(Field** matrix, Robots* robot, int coord_x, int coord_y, int counter) 
{
  if ((matrix == nullptr) || (robot == nullptr)){
    return MEMORY_ALLOC_ERROR;
  }

  char symbol = robotNames[counter]; // A B C or D

  matrix[coord_x][coord_y].createRobot(symbol); // in matrix swapping an _ with robot symbol

  robot[counter] = Robots(symbol, coord_x, coord_y); // new object in the Robots class

  return SUCCESS;
}


int getDistanceToEnd(Field** matrix, int x, int y)
{
  int distance = 0;
  distance = abs(x - Field::endCoordX) + abs(y - Field::endCoordY);

  return distance;
}


int getDistanceToRobot(Field** matrix, int x, int y, int robot_x, int robot_y)
{
  int distance = 0;
  distance = abs(x - robot_x) + abs(y - robot_y);

  return distance;
}


int generateRandomCoords(Field** matrix, Robots* robot, int counter, int& x_coord, int& y_coord)
{
  bool not_occupied;
  bool in_level;
  bool too_close;

  const int matH = Field::matrixHeight;
  const int matW = Field::matrixWidth;

  do
  {
    not_occupied = true;
    in_level = true;
    too_close = true;

    x_coord = 1 + rand()%(matW - 1);
    y_coord = 1 + rand()%(matH - 1);

    //this shouldn't ever happen but just to be sure for now
    if((x_coord <= 0 || x_coord >= matW) || (y_coord <= 0 || y_coord >= matH))
    {
      in_level = false;
      //gl::displayMessage("Out of bounds!");
    }

    else if(matrix[x_coord][y_coord].getSymbol() != '_')
    {
      not_occupied = false;
      //gl::displayMessage("Tile not empty!");
    } 

    else if(getDistanceToEnd(matrix, x_coord, y_coord) < 6)
    {
      too_close = false;
    }

    for(int i = 0; i < counter; i++)
    {
      if(getDistanceToRobot(matrix, x_coord, y_coord, robot[i].coords[0], robot[i].coords[1]) < 2)
      {
        too_close = false;
      }
    }


  } while(!not_occupied || !in_level || !too_close);
  

  return SUCCESS;
}


int createRobots(Field** matrix, Robots* robot, int robotNum)
{
  if ((matrix == nullptr) || (robot == nullptr)){
    return MEMORY_ALLOC_ERROR;
  }

  int counter = 0; //uses robotNames to get symbol
  int coords_x = 0;
  int coords_y = 0;
  bool manual_input = false;
  char input = ' ';

  srand(time(NULL));

  std::cout<<std::endl; //make gl::newLine
  gl::displayMessage("Would you like to insert them manually (y/n):");
  std::cin>>input;

  if(input == 'y'){
    manual_input = true;
  }

  //*random option
  if (!manual_input)
  {

    for (counter=0; counter<robotNum; counter++)
    {
      generateRandomCoords(matrix, robot, counter, coords_x, coords_y);

      gl::displayMessageInt("Adding robot ", counter+1);
      addRobotToMatrix(matrix, robot, coords_x, coords_y, counter);
    }


  } //end of random part
  
  else
  {
    //*manual option
    gl::displayMessage("");

    //creating robotNum amount of robots (objects of robots class and in matrix)
    for (counter=0; counter<robotNum; counter++)
    {
      gl::displayMessageChar("ROBOT ", robotNames[counter]);

      //inputing coords and cheking if the given coords are empty/inside the matrix
      do
      {
        gl::displayMessage("enter x and y coords: ");
        std::cin >> coords_x;
        std::cin >> coords_y;

        if ((coords_x < 0) || (coords_y < 0))
        {
          gl::displayMessage("coordinates can't be neagtive!");
          continue;
        }
        else if((coords_x > Field::matrixWidth-1) || (coords_y > Field::matrixHeight-1))
        {
          gl::displayMessage("coordinates are outside of the matrix!");
          gl::displayMessageInt("keep width under ", Field::matrixWidth);
          gl::displayMessageInt("keep height under ", Field::matrixHeight);
          continue;
        }
        else if(!(matrix[coords_y][coords_x].getIsEmpty()))
        {
          gl::displayMessage("coordinates are not empty!");
          continue;
        }

        break;
        
      } while(1);
      
      gl::displayMessage("");
      addRobotToMatrix(matrix, robot, coords_x, coords_y, counter);
    }
  
  }//end of manual part


  

  return SUCCESS;
}


int prepareMove(Field** matrix, Robots* robot, int counter)
{
  int directions[4][2] = {{-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}};
  int current_pos[2];
  int rand_choice = -1;
  bool possibleMove = false; // if this stays false don't call moveRobot
  current_pos[0] = robot[counter].coords[0];
  current_pos[1] = robot[counter].coords[1];

  //down
  if(!(matrix[(current_pos[0] + 1)][current_pos[1]].getIsWall()))
  {
    if(!(matrix[(current_pos[0] + 1)][current_pos[1]].getIsRobot()))
    {
      directions[0][0] = (current_pos[0] + 1);
      directions[0][1] = (current_pos[1]);
      possibleMove = true;
    }
    else
    {
      gl::displayMessage("Hit robot!");
    }

  }
  else
  {
    robot[counter].foundNewWall(current_pos[0] + 1, current_pos[1]);
  }


  //right
  if(!(matrix[(current_pos[0])][current_pos[1] + 1].getIsWall()))
  {
    if(!(matrix[(current_pos[0])][current_pos[1]+1].getIsRobot()))
    {
      directions[1][0] = (current_pos[0]);
      directions[1][1] = (current_pos[1]+1);
      possibleMove = true;
    }
    else
    {
      gl::displayMessage("Hit robot!");
    }
  }
  else
  {
    robot[counter].foundNewWall(current_pos[0], current_pos[1] + 1);
  }

  //up
  if(!(matrix[(current_pos[0] - 1)][current_pos[1]].getIsWall()))
  {
    if(!(matrix[(current_pos[0] - 1)][current_pos[1]].getIsRobot()))
    {
      directions[2][0] = (current_pos[0] - 1);
      directions[2][1] = (current_pos[1]);
      possibleMove = true;
    }
    else
    {
      gl::displayMessage("Hit robot!");
    }
  }
  else
  {
    robot[counter].foundNewWall(current_pos[0] - 1, current_pos[1]);
  }

  //left
  if(!(matrix[(current_pos[0])][current_pos[1] - 1].getIsWall()))
  {
    if(!(matrix[(current_pos[0])][current_pos[1]-1].getIsRobot()))
    {
      directions[3][0] = (current_pos[0]);
      directions[3][1] = (current_pos[1]-1);
      possibleMove = true;
    }
    else
    {
      gl::displayMessage("Hit robot!");
    }
  }
  else
  {
    robot[counter].foundNewWall(current_pos[0], current_pos[1] - 1);
  }
  
  if (!possibleMove)
  {
    gl::displayMessage("No empty coords!");
    return SUCCESS;
  }

  do
  {
    rand_choice = rand()%4; //0, 1, 2, 3

  }while(directions[rand_choice][0] == -1); //it doesn't choose ones with wall

  gl::displayMessage("New cords!");
  gl::displayMessageInt("x: ", directions[rand_choice][0]);
  gl::displayMessageInt("y: ", directions[rand_choice][1]); 

  moveRobot(matrix, robot, directions[rand_choice][0], directions[rand_choice][1], counter);

  return SUCCESS;
}


int moveRobot(Field** matrix, Robots* robot, int coord_x, int coord_y, int counter)
{
  if ((matrix == nullptr) || (robot == nullptr)){
    return MEMORY_ALLOC_ERROR;
  }

  int robotCoord_x = robot[counter].coords[0];
  int robotCoord_y = robot[counter].coords[1];
  //these are the old robot coords
  //new coords are coord_x and coord_y

  robot[counter].newCoords(coord_x, coord_y);
  //setting new coords in robot object

  //if at end don't swapObj - just erase robot from field 
  if ( !(matrix[coord_x][coord_y].getIsEnd()) )
  { 
    matrix[robotCoord_x][robotCoord_y].swapObj(matrix[coord_x][coord_y]);
    //swapping objects in matrix
  }
  else
  {
    matrix[robotCoord_x][robotCoord_y].beEmpty();
    robot[counter].setAtEnd();
    std::cout << "Robot " << robotNames[counter] << " has reached the end!" << std::endl;

  }


  return SUCCESS;
}


int showResults(Robots* robot, int robotNum)
{
  gl::displayMessage("\n=====>RESULTS<=====\n");

  for(int i = 0; i < robotNum; i++)
  {
    if( robot[i].getIsAtEnd() )
    {
      std::cout << "Robot " << robotNames[i] << " has reached the end in " << robot[i].getMoves() << " moves!"<<std::endl;
    }
    else
    {
      std::cout << "Robot " << robotNames[i] << " didn't reached the end!" << std::endl;
    }
  }

  gl::displayMessage("\n===================\n");
  
  return SUCCESS;
}

int showReplay(Field** matrix)
{
  char temp = ' ';
  gl::displayMessage("Watch game replay?(y/n)");

  std::cin>> temp;
  if (temp=='y')
  {
    	matrix[Field::endCoordX][Field::endCoordY].replayGame();
  }

  return SUCCESS;
}
//TODO
  //// BUG: robots seem to freeze after "touching" each other ==> INVASTIGATE  - DONE
  //// in some way avoid robots spawning too close to finish/each other - DONE
  //// 1. make it so that when the robot is about to hit the $ it stops and despawns (to avoid $ moving)
  //// 2. implement actual mainloop with while which ends when all robots finish or too many steps
  //// BUG -if robots are to close it just breaks
  //// does check if too close to end affects manual input? 
  //*update prepareMove to take into account previous moves?
  //*check whether knownWalls actually stores them correctlly
  //// add prepareMove for robot which calls moveRobot
  ////fix robotName issue
  //*for int functions check msg
  //*create destructors
  //* IDEAS
  //*create list with all outputs? that way we can clear screen cmd - more clean and at end have watch highliths/replay option
//TODO  