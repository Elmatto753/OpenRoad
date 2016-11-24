#include <iostream>
#include <fstream>
#include "XMLParser.h"

class OBJWrite
{
public:
  OBJWrite();
  ~OBJWrite();

  // Write a string to the OBJ file
  void writeToOBJ(std::string _input);


private:

  std::ofstream objfile;

};
