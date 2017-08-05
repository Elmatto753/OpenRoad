#ifndef XMLPARSER_H_
#define XMLPARSER_H_

#include <fstream>
#include <string>
#include <map>
#include <iostream>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>

//individual node data
struct node
{
    int nodeRef = 0;
    uint64_t nodeID;
    float nodeLat;
    float nodeLon;
    bool isIntersection = false;
    bool inNewNetwork = false;
    //set any outlying nodes to unfinished (only the node at the end or beginning of the way)
    bool isUnfinished = false;
    unsigned int numIntersections = 0;
    std::vector<std::string> intersectsWith;
    std::map<unsigned int, node *> next;
};

//road segment data - contains nodes
struct way
{
    unsigned int wayRef = 0;
    uint64_t wayID;
    //storing all the node reference that are inside the way
    std::vector<node> nodesInWay;
    std::vector<node> intersections;
    std::string name;
};

//ability to store original road network and extended network
class network
{
public :

    network();
    ~network();

    std::vector<node> nodes;
    std::vector<way> ways;
    node currentNode;
    way currentWay;
};

class XMLParse
{
public :
    XMLParse();
    ~XMLParse();

    //original OpenStreetMap network
    network Network;
    //extended road network
    network NewNetwork;

    typedef boost::tokenizer<boost::char_separator<char> >tokenizer;

    //functions
    void parseXML( const std::string &_filename);
    void checkIntersections();
    void unfinishedNodes();

    //variables
    unsigned int m_nodeRef = 0;
    unsigned int m_wayRef = 0;
    float m_minLat, m_minLon, m_maxLat, m_maxLon;
};

#endif //_XMLPARSER_H_
