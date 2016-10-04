#include <iostream>
#include <fstream>
#include <string>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>


typedef boost::tokenizer<boost::char_separator<char> >tokenizer;

void parseXML( const std::string &_filename);

int main(int argc, char *argv[])
{
  std::cout<<"time to parse some shit\n";

  parseXML( "data/map.osm" );
}


void parseXML( const std::string &_filename)
{
  std::fstream fileIn;
  fileIn.open( _filename.c_str(), std::ios::in );

  if( !fileIn.is_open() )
  {
      std::cerr<<"Could not open "<<_filename<<"\n";
      exit( EXIT_FAILURE );
  }

  boost::char_separator<char> sep( " " );
  std::string lineBuffer;

  while( !fileIn.eof() )
  {
    getline( fileIn, lineBuffer, '\n' );

    if( lineBuffer.size() != 0 )
    {
      tokenizer tokens( lineBuffer, sep );
//      tokenizer::iterator firstWord = tokens.begin();

      for(tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter)
      {
        std::cout<< *tok_iter;
      }
      std::cout<<"\n";


      //++firstWord;
     }

  }

  fileIn.close();

}
