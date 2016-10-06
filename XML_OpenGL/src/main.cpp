#include <QtGui/QGuiApplication>
#include <iostream>
#include "GLwindow.h"
#include <fstream>
#include <string>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>
#include <stdio.h>
#include <stdlib.h>

/*int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);
    GLWindow window;
    window.resize(1024,720);
    window.show();

    return app.exec();
}*/

typedef boost::tokenizer<boost::char_separator<char> >tokenizer;

void parseXML( const std::string &_filename);

int main(int argc, char *argv[])
{
  QGuiApplication app(argc, argv);
  GLWindow window;
  window.resize(1024,720);
  window.show();



  std::cout<<"time to parse some shit\n";

  parseXML( "data/map.osm" );

  return app.exec();
}


void parseXML( const std::string &_filename)
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

  // Set up node referencing
  int nodeRef = 0;
  std::vector<float> nodeLat;
  std::vector<float> nodeLon;
  float minLat, minLon, maxLat, maxLon;

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
          nodeLat.push_back(boost::lexical_cast<float>( *tok_iter ));
        }

        else if( *tok_iter == "lon" )
        {
          std::cout<<"lon="<<*++tok_iter<<" ";
          nodeLon.push_back(boost::lexical_cast<float>( *tok_iter ));
          ++nodeRef;
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
