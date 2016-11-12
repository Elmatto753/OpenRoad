#include "XMLParser.h"

XMLParse::XMLParse()
{

}


XMLParse::~XMLParse()
{

}

void XMLParse::parseXML( const std::string &_filename)
{
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
          //currentNode.nodeID = (boost::lexical_cast<uint64_t>( *tok_iter ));
          std::stringstream ss;
          ++tok_iter;
          ss << *++tok_iter;
          ss >> currentNode.nodeID;
          std::cout<<"ID = "<< currentNode.nodeID<<"\n";

        }

        //std::cout<< *tok_iter;
        // Look for latitude and longitude values
        else if( *tok_iter == "lat" )
        {
         // std::cout<<"lat="<<*++tok_iter<<" ";
          ++tok_iter;
          currentNode.nodeLat=(boost::lexical_cast<float>( *tok_iter ));
        }

        else if( *tok_iter == "lon" )
        {
          ++tok_iter;
         // std::cout<<"lon="<<*++tok_iter<<" ";
          currentNode.nodeLon=(boost::lexical_cast<float>( *tok_iter ));
          currentNode.nodeRef=nodeRef;

          //if all valid (e.g. not outliers) then push back node
          if((currentNode.nodeLat>=minLat)&&(currentNode.nodeLat<=maxLat)&&
             (currentNode.nodeLon>=minLon)&&(currentNode.nodeLon<=maxLon))
          {
              nodes.push_back(currentNode);
              ++nodeRef;
              std::cout<<"noderef = "<<nodeRef<<"\n";
          }
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
          //std::cout<<"ID = "<<currentWay.wayID<<" ";
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
          ++tok_iter;
          //currentWay.name = (boost::lexical_cast<char>( *++tok_iter ));
        }

        else if ( *tok_iter == "</way>" && inWay == true )
        {
          currentWay.wayRef = wayRef;
          ways.push_back(currentWay);
          wayRef++;

          inWay = false;
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
