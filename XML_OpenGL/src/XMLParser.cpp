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

  while( !fileIn.eof() )
  {
    // Get a line and turn it into tokens
    getline( fileIn, lineBuffer, '\n' );

    if( lineBuffer.size() != 0 )
    {
      tokenizer tokens( lineBuffer, sep );

      // Iterate through looking for nodes
      for(tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter)
      {
        if( *tok_iter == "minlat" )
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

        //std::cout<< *tok_iter;
        else if( *tok_iter == "lat" )
        {
          std::cout<<"lat="<<*++tok_iter<<" ";          
          currentNode.nodeLat=(boost::lexical_cast<float>( *tok_iter ));
        }

        else if( *tok_iter == "lon" )
        {
          std::cout<<"lon="<<*++tok_iter<<" ";
          currentNode.nodeLon=(boost::lexical_cast<float>( *tok_iter ));
          currentNode.nodeRef=nodeRef;

          //if all valid (e.g. not outliers) then push back node
          if((currentNode.nodeLat>=minLat)&&(currentNode.nodeLat<=maxLat)&&
             (currentNode.nodeLon>=minLon)&&(currentNode.nodeLon<=maxLon))
          {
              nodes.push_back(currentNode);
              ++nodeRef;
          }
        }

      }
      //std::cout<<"\n";


      //++firstWord;
     }

  }

  std::cout<<"minlat="<<minLat<<" minLon="<<minLon<<" maxlat="<<maxLat<<" maxLon="<<maxLon;

  // Close the file
  fileIn.close();

}
