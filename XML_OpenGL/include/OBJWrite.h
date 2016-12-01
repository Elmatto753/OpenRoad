#include <iostream>
#include <fstream>
#include "XMLParser.h"

class OBJWrite
{
public:
  OBJWrite();
  ~OBJWrite();

  void clearOBJ();
  // Write a string to the OBJ file
  void writeToOBJ(std::string _input);


private:

  std::ofstream objfile;

};
