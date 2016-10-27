#ifndef XMLPARSER_H__
#define XMLPARSER_H__

#include <fstream>
#include <string>
#include "iostream"
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>

//node data
struct node
{
    int nodeRef;
    //uint32 is not enough, thus uint64
    uint64_t nodeID;
    float nodeLat;
    float nodeLon;
    //TBA
    //float way;
};

//way data
struct way
{
  int wayRef;
  uint64_t wayID;
  std::vector<uint64_t> nodesInWay;
  char name;
};

class XMLParse
{
public :

  XMLParse();

  ~XMLParse();

  typedef boost::tokenizer<boost::char_separator<char> >tokenizer;

  void parseXML( const std::string &_filename);

  std::vector<node> nodes;
  std::vector<way> ways;
  node currentNode;
  way currentWay;

  // Set up node referencing
  int nodeRef = 0;
  int wayRef = 0;
  float minLat, minLon, maxLat, maxLon;

};

#endif
