#include <iostream>
#include <fstream>

void main(){

  char symbol = 'A';
  std::string symb(1, symbol);
  int i = 0;
  std::ofstream outfile;
  //std::string filename = "moves.txt";
  std::string filename = symb + "moves.txt";
  outfile.open(filename, std::ios_base::app);//std::ios_base::app
  outfile << "Movment History: \n"; 

  for (i = 0; i<5; i++)
  {
    outfile << "\t=> 1" << "\n";
  }


}