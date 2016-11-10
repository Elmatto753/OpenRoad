#include "GLwindow.h"

#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif

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
    gluLookAt(0,0,-120,0,0,0,0,1,0);
    startTimer(1);


    std::cout<<"time to parse some shit\n";

    //for crazy mac usage
   // Parser.parseXML( "/Users/edina/Documents/3rd year/Collab Research Project/OpenRoad/XML_OpenGL/data/map.osm" );
    //for normal people
    Parser.parseXML("data/map.osm");
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

  glPointSize(2.0f);
//  for(int i = 0; i<=Parser.nodeRef; i++)
//  {
//    {
//        glPushMatrix();
//        glRotatef(90, 0.0, 0.0, 1.0);
//        glTranslatef(-50.0f,-50.0f,0.0f);
//        glBegin(GL_POINTS);
//          glColor3f(1.0,1.0,1.0);
//          //drawing nodes
//          glVertex3f(((Parser.nodes[i].nodeLat-Parser.minLat)/latInterval) * 100, ((Parser.nodes[i].nodeLon-Parser.minLon)/lonInterval) * 100, 0.0f);
//        glEnd();
//        glPopMatrix();
//    }
//  }
  for( uint i = 0; i<Parser.wayRef; i++)
  {
    for(uint j = 1; j<Parser.ways[i].nodesInWay.size(); j++)
    {
      //std::cout<<"size = "<<Parser.ways[i].nodesInWay.size()<<"\n";
//      for(uint k = 0; k<=Parser.nodeRef; k++)
//      {

//        if(Parser.nodes[k].nodeID == Parser.ways[i].nodesInWay[j])
//        {
//          toDraw.push_back(Parser.nodes[k]);

//        }

//      }

        glPushMatrix();
        glRotatef(90, 0.0, 0.0, 1.0);
        glTranslatef(-50.0f,-50.0f,0.0f);
        glBegin(GL_LINES);
        glColor3f(1.0,1.0,1.0);
        //drawing ways

          glVertex3f(((Parser.nodes[Parser.ways[i].nodesInWay[j - 1]].nodeLat-Parser.minLat)/latInterval) * 100, ((Parser.nodes[Parser.ways[i].nodesInWay[j - 1]].nodeLon-Parser.minLon)/lonInterval) * 100, 0.0f);

          glVertex3f(((Parser.nodes[Parser.ways[i].nodesInWay[j]].nodeLat-Parser.minLat)/latInterval) * 100, ((Parser.nodes[Parser.ways[i].nodesInWay[j]].nodeLon-Parser.minLon)/lonInterval) * 100, 0.0f);


        glEnd();
        glPopMatrix();

    }

  }
}
