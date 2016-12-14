#include "XMLParser.h"

XMLParse::XMLParse()
{

}


XMLParse::~XMLParse()
{

}

void XMLParse::parseXML( const std::string &_filename)
{
  nodeRef = 0;
  wayRef = 0;
  nodes.clear();
  ways.clear();
  // Open XML file
  std::fstream fileIn;
  fileIn.open( _filename.c_str(), std::ios::in );

  if( !fileIn.is_open() )
  {
      std::cerr<<"Could not open "<<_filename<<"\n";
      exit( EXIT_FAILURE );
  }

  // Define what separates words
  boost::char_separator<char> sep( " =\"" );
  std::string lineBuffer;
  bool inWay = false;
  bool storeWay = false;
  uint lineNum = 0;
  uint errLineNum = 0;

  while( !fileIn.eof() )
  {

    // Get a line and turn it into tokens
    getline( fileIn, lineBuffer, '\n' );
    ++lineNum;

    if( lineBuffer.size() != 0 )
    {
      tokenizer tokens( lineBuffer, sep );

      // Iterate through looking for nodes
      for(tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter)
      {
        //define boundries
        if( *tok_iter == "  " )
        {
          tok_iter++;
        }

        else if( *tok_iter == "minlat" )
        {
          minLat = boost::lexical_cast<float>( *++tok_iter );
        }

        else if( *tok_iter == "maxlat" )
        {
          maxLat = boost::lexical_cast<float>( *++tok_iter );
        }

        else if( *tok_iter == "minlon" )
        {
          minLon = boost::lexical_cast<float>( *++tok_iter );
        }

        else if( *tok_iter == "maxlon" )
        {
          maxLon = boost::lexical_cast<float>( *++tok_iter );
        }
        // look for this token to create node id, as id token is used elsewhere in the XML
        // iterate tokens twice instead

        else if( *tok_iter == "<node" )
        {
          std::stringstream ss;
          if( *++tok_iter == "id")
          {
            ss << *++tok_iter;
            ss >> currentNode.nodeID;
          }
        }


        // Look for latitude and longitude values
        else if( *tok_iter == "lat" )
        {

          ++tok_iter;
          currentNode.nodeLat=(boost::lexical_cast<float>( *tok_iter ));
        }

        else if( *tok_iter == "lon" )
        {
          ++tok_iter;

          currentNode.nodeLon=(boost::lexical_cast<float>( *tok_iter ));
          currentNode.nodeRef=nodeRef;

          //if all valid (e.g. not outliers) then push back node
//          if((currentNode.nodeLat>=minLat)&&(currentNode.nodeLat<=maxLat)&&
//             (currentNode.nodeLon>=minLon)&&(currentNode.nodeLon<=maxLon))
//          {

              nodes.push_back(currentNode);
              ++nodeRef;
//          }
        }

        else if( *tok_iter == "<way" )
        {
          if( inWay == true )
          {
            std::cerr<<"Warning: A way was opened without being closed. Unclosed way at line: "<<errLineNum<<"\n";
          }
          errLineNum = lineNum;
          inWay = true;
        }

        else if( *tok_iter == "id" && inWay ==true )
        {
          std::stringstream ss;
          ss << *++tok_iter;
          ss >> currentWay.wayID;
        }

        else if( *tok_iter == "ref" && inWay == true )
        {
          std::stringstream ss;
          uint64_t temp;
          ss << *++tok_iter;
          ss >> temp;
          for(uint i = 0; i <= nodeRef; i++)
          {
            if(nodes[i].nodeID == temp)
            {
              //std::cout<<"i = "<<i<<"\n";
              currentWay.nodesInWay.push_back( i );
              break;
            }

          }

          // may have to check if node reference is in vector of nodes here
        }

        else if( *tok_iter == "name" && inWay == true )
        {
          std::stringstream ss;
          while( *++tok_iter != "/>" )
          {
            if(*tok_iter != "v")
            {
              ss << *tok_iter;
            }
          }
          ss >> currentWay.name;
          //std::cout<< currentWay.name;
        }

        else if ( *tok_iter == "highway")
        {
          storeWay = true;
        }

        else if ( *tok_iter == "</way>" && inWay == true )
        {
          inWay = false;
          if( storeWay == true )
          {
            currentWay.wayRef = wayRef;
            ways.push_back(currentWay);

            wayRef++;
          }
          currentWay.nodesInWay.clear();
          storeWay = false;

        }

      }

      //std::cout<<"\n";


      //++firstWord;
    }

  }

  std::cout<<"\n"<<wayRef<<"\n";

  std::cout<<"minlat="<<minLat<<" minLon="<<minLon<<" maxlat="<<maxLat<<" maxLon="<<maxLon;

  // Close the file
  fileIn.close();

}

void XMLParse::checkIntersections()
{
  for(uint i = 0; i<ways.size(); i++)
  {
    for(uint j = 0; j<ways[i].nodesInWay.size(); j++)
    {
//      node n = ways[i].nodesInWay[j];

      for(uint k = 0; k<ways.size(); k++)
      {
        if(i == k)
        {
          continue;
        }
        else
        {
          for(uint l = 0; l<ways[k].nodesInWay.size(); l++)
          {
            if(ways[i].nodesInWay[j] == ways[k].nodesInWay[l])
            {
              ways[i].intersections.push_back(ways[i].nodesInWay[j]);

            }
          }
        }
      }

    }
  }
  for(int i = 0; i<ways.size(); i++)
  {
    std::cout<<" size = "<<ways[i].intersections.size()<<"\n";
  }
  std::cout<<"hi";
}
