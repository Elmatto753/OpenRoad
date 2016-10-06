#ifndef XMLPARSER_H__
#define XMLPARSER_H__

#include <fstream>
#include <string>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>

class XMLParse
{
public :

  XMLParse();

  ~XMLParse();

  typedef boost::tokenizer<boost::char_separator<char> >tokenizer;

  void parseXML( const std::string &_filename);

  // Set up node referencing
  int nodeRef = 0;
  std::vector<float> nodeLat;
  std::vector<float> nodeLon;
  float minLat, minLon, maxLat, maxLon;


};

#endif
