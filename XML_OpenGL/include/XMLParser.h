#ifndef XMLPARSER_H__
#define XMLPARSER_H__

#include <fstream>
#include <string>
#include <map>
#include "iostream"
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>

//node data
struct node
{
    int nodeRef = 0;
    uint64_t nodeID;
    float nodeLat;
    float nodeLon;
    bool isIntersection = false;
    uint numIntersections = 0;
    std::vector<std::string> intersectsWith;
    std::map<uint, node *> next;
};

//way data
struct way
{
  uint wayRef = 0;
  uint64_t wayID;
  //storing all the node reference that are inside the way
  std::vector<node> nodesInWay;
  std::vector<node> intersections;
  std::string name;
};



class XMLParse
{
public :

  XMLParse();

  ~XMLParse();

  typedef boost::tokenizer<boost::char_separator<char> >tokenizer;

  void parseXML( const std::string &_filename);
  void checkIntersections();

  std::vector<node> nodes;
  std::vector<way> ways;
  node currentNode;
  way currentWay;

  // Set up node referencing
  uint nodeRef = 0;
  uint wayRef = 0;
  float minLat, minLon, maxLat, maxLon;

};

#endif
