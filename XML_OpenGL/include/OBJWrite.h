#ifndef OBJWRITE_H_
#define OBJWRITE_H_

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

#endif //_OBJWRITE_H_
