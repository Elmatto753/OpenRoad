#include "OBJWrite.h"

OBJWrite::OBJWrite()
{
  // Prepare the .obj for writing, and empty the file when opening
  objfile.open("output/map.obj", std::ofstream::out | std::ofstream::trunc);
  if(objfile.is_open())
  {
    objfile << "# This file uses centimeters as units for non-parametric coordinates.\n\n";
    objfile << "mtllib map.mtl\n";
    objfile << "g default\n";
    objfile.close();
  }
  else
  {
    std::cerr<<"Could not create/open file";
  }
}

OBJWrite::~OBJWrite()
{

}

void OBJWrite::writeToOBJ(std::string _input)
{
  objfile.open("output/map.obj", std::ios::app);
  objfile << _input;
  objfile.close();
}
