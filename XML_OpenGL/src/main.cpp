#include <QtGui/QGuiApplication>
#include <iostream>
#include "GLwindow.h"
#include "XMLParser.h"
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

//typedef boost::tokenizer<boost::char_separator<char> >tokenizer;

//void parseXML( const std::string &_filename);

int main(int argc, char *argv[])
{
  QGuiApplication app(argc, argv);
  GLWindow window;
  window.resize(720,720);
  window.show();




  return app.exec();
}



