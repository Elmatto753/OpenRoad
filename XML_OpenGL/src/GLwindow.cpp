#include "GLwindow.h"

//again for normal people (havn't tested the ifdef on linux yet)
//#include <GL/glu.h>
//for mac
#include <OpenGL/glu.h>

#include <QKeyEvent>
#include <QGuiApplication>
#include "iostream"
#include <stdio.h>
#include <stdlib.h>

GLWindow::GLWindow()
{
    setTitle("Simple GL Window");
    m_y=0.0f;
}

GLWindow::~GLWindow()
{

}

void GLWindow::initializeGL()
{
    glClearColor(0.6,  0.6, 0.6, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(65,float(width()/height()),0.1,1000);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_NORMALIZE);
    glLoadIdentity();
    gluLookAt(0,0,100,0,0,0,0,1,0);
    startTimer(1);


    std::cout<<"time to parse some shit\n";

    //for crazy mac usage
    Parser.parseXML( "/Users/edina/Documents/3rd year/Collab Research Project/OpenRoad/XML_OpenGL/data/map.osm" );
    //for normal people
    //Parser.parseXML("data/map.osm");
}

void GLWindow::resizeGL(int _w, int _h)
{
    glViewport(0,0,_w,_h);
}

void GLWindow::paintGL()
{

    //lat long out of 100
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //right line
    glPushMatrix();
    glTranslatef(50.0f,0.0f,0.0f);
    glBegin(GL_LINES);
        glColor3f(1.0,0.0,0.0);
        glVertex3f(0.0,50.0,0.0);

        glVertex3f(0.0,-50.0,0.0);
    glEnd();
    glPopMatrix();
    //left line
    glPushMatrix();
    glTranslatef(-50.0f,0.0f,0.0f);
    glBegin(GL_LINES);
        glColor3f(1.0,0.0,0.0);
        glVertex3f(0.0,50.0,0.0);

        glVertex3f(0.0,-50.0,0.0);
    glEnd();
    glPopMatrix();
    //top line
    glPushMatrix();
    glTranslatef(0.0f,50.0f,0.0f);
    glBegin(GL_LINES);
        glColor3f(1.0,0.0,0.0);
        glVertex3f(-50.0,0.0,0.0);

        glVertex3f(50.0,0.0,0.0);
    glEnd();
    glPopMatrix();
    //bottom line
    glPushMatrix();
    glTranslatef(0.0f,-50.0f,0.0f);
    glBegin(GL_LINES);
        glColor3f(1.0,0.0,0.0);
        glVertex3f(-50.0,0.0,0.0);

        glVertex3f(50.0,0.0,0.0);
    glEnd();
    glPopMatrix();

    drawNodes();

}

void GLWindow::timerEvent(QTimerEvent *)
{
    update();
}

void GLWindow::keyPressEvent(QKeyEvent *_event)
{
    switch(_event->key())
    {
        case Qt::Key_Escape : QGuiApplication::exit(0); break;
        case Qt::Key_W : glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
        case Qt::Key_S : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
    }
}

void GLWindow::drawNodes()
{
  float lonInterval = Parser.maxLon-Parser.minLon;
  float latInterval = Parser.maxLat-Parser.minLat;
  float multiplierLat;
  float multiplierLon;

  //working out how much to scale by
  multiplierLat=100/latInterval;
  multiplierLon=100/lonInterval;

  glPointSize(2.0f);
  glPushMatrix();
  glTranslatef(0.0f,-50.0f,0.0f);
  glBegin(GL_POINTS);
      glColor3f(1.0,1.0,1.0);
      //don't know why this doesn't work :o
      glVertex3f(-50+((Parser.nodeLat[1]-Parser.minLat)*multiplierLat), 0.0, -50+((Parser.nodeLon[1]-Parser.minLon)*multiplierLon));
  glEnd();
  glPopMatrix();

  // Point test
  /*for(int i=0; i<Parser.nodeRef; i++)
  {
    glPointSize(2.0f);
    glPushMatrix();
    glTranslatef(0.0f,-50.0f,0.0f);
    glBegin(GL_POINTS);
        glColor3f(1.0,1.0,1.0);
        glVertex3f(Parser.nodeLat[i], 0.0, Parser.nodeLon[i]);
        //glVertex3f(Parser.nodeLat.at(i) ,0.0,Parser.nodeLon.at(i));
    glEnd();
    glPopMatrix();
  }*/
}
