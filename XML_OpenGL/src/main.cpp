//#include "GLwindow.h"
//#include "XMLParser.h"
//#include <QtGui/QGuiApplication>
//#include <iostream>
//#include <stdio.h>
//#include <stdlib.h>
#include <QApplication>
#include "mainwindow.h"

int main(int argc, char **argv)
{
  QApplication a(argc, argv);
  MainWindow w;

  w.show();

  return a.exec();
}



