#include "XMLParser.h"

network::network()
{

}

network::~network()
{

}

XMLParse::XMLParse()
{

}


XMLParse::~XMLParse()
{

}

void XMLParse::parseXML(const std::string &_filename)
{
  nodeRef = 0;
  wayRef = 0;
  Network.nodes.clear();
  Network.ways.clear();
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
            ss >> Network.currentNode.nodeID;
          }
        }


        // Look for latitude and longitude values
        else if( *tok_iter == "lat" )
        {

          ++tok_iter;
          Network.currentNode.nodeLat=(boost::lexical_cast<float>( *tok_iter ));
        }

        else if( *tok_iter == "lon" )
        {
          ++tok_iter;

          Network.currentNode.nodeLon=(boost::lexical_cast<float>( *tok_iter ));
          Network.currentNode.nodeRef=nodeRef;


          Network.nodes.push_back(Network.currentNode);
          ++nodeRef;
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
          ss >> Network.currentWay.wayID;
        }

        else if( *tok_iter == "ref" && inWay == true )
        {
          std::stringstream ss;
          uint64_t temp;
          ss << *++tok_iter;
          ss >> temp;
          for(uint i = 0; i < nodeRef; i++)
          {
            if(Network.nodes[i].nodeID == temp)
            {
              //std::cout<<"i = "<<i<<"\n";
              Network.currentWay.nodesInWay.push_back( Network.nodes[i] );
              break;
            }

          }

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
          ss >> Network.currentWay.name;
        }

        else if ( *tok_iter == "highway" && inWay == true)
        {
          storeWay = true;
        }

        else if ( *tok_iter == "</way>" && inWay == true )
        {
          inWay = false;
          if( storeWay == true )
          {
            uint j;
            Network.currentWay.wayRef = wayRef;
            // Building out a map of "next" nodes for each node in a way
            // "next" is mapped to a corresponding way, in case a node is in more than one way
            for(j = 1; j < Network.currentWay.nodesInWay.size(); j++)
            {
              Network.currentWay.nodesInWay[j - 1].next[Network.currentWay.wayRef] = &Network.currentWay.nodesInWay[j];
            }
            // The final node in a way has a null next
            Network.currentWay.nodesInWay[j - 1].next[Network.currentWay.wayRef] = nullptr;
            Network.ways.push_back(Network.currentWay);

            wayRef++;
          }
          Network.currentWay.nodesInWay.clear();
          Network.currentWay.name.clear();
          storeWay = false;
        }
      }
    }
  }

  std::cout<<"\n"<<wayRef<<"\n";

  std::cout<<"minlat="<<minLat<<" minLon="<<minLon<<" maxlat="<<maxLat<<" maxLon="<<maxLon;

  // Close the file
  fileIn.close();

}

void XMLParse::checkIntersections()
{
  for(uint i = 0; i<Network.ways.size(); i++)
  {
    for(uint j = 0; j<Network.ways[i].nodesInWay.size(); j++)
    {
      for(uint k = 0; k<Network.ways.size(); k++)
      {
        if(i == k)
        {
          continue;
        }
        else
        {
          for(uint l = 0; l<Network.ways[k].nodesInWay.size(); l++)
          {
            if(Network.ways[i].nodesInWay[j].nodeID == Network.ways[k].nodesInWay[l].nodeID && Network.ways[i].nodesInWay[j].nodeRef != int(Network.nodes.size()))
            {
              Network.ways[i].nodesInWay[j].isIntersection = true;
              Network.ways[i].nodesInWay[j].numIntersections++;
              Network.ways[i].nodesInWay[j].intersectsWith.push_back(Network.ways[k].name);
              Network.ways[i].intersections.push_back(Network.ways[i].nodesInWay[j]);
            }
            else
            {
             // std::cout<<"size = "<<nodes.size()<<"\n";
            }
          }
        }
      }
      if(Network.ways[i].nodesInWay[j].intersectsWith.size() != 0)
      {
        std::cout<<"node "<<Network.ways[i].nodesInWay[j].nodeRef<<" is in "<<Network.ways[i].name<<", has "<<Network.ways[i].nodesInWay[j].numIntersections<<" intersections and intersects with:\n";
        for(uint m = 0; m < Network.ways[i].nodesInWay[j].intersectsWith.size(); m++)
        {
          std::cout<<Network.ways[i].nodesInWay[j].intersectsWith[m]<<"\n";
        }
      }

    }
  }
}


