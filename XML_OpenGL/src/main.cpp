//#include "GLwindow.h"
//#include "XMLParser.h"
//#include <QtGui/QGuiApplication>
//#include <iostream>
//#include <stdio.h>
//#include <stdlib.h>
#include <QApplication>
#include "mainwindow.h"

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

int main(int argc, char **argv)
{
//  QGuiApplication app(argc, argv);
//  GLWindow window;
//  window.resize(720,720);
//  window.show();
//  return app.exec();

  QApplication a(argc, argv);
  MainWindow w;
//  w.resize(720, 720);
  w.show();

  return a.exec();
}



