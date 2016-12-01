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

GLWindow::GLWindow(QWidget *_parent) :
  QOpenGLWidget(_parent)
{
//    setTitle("Simple GL Window");
    m_y=0.0f;
}

GLWindow::~GLWindow()
{

}

void GLWindow::test(bool)
{
  Parser.parseXML("data/map.osm");
}

QString GLWindow::openFileBrowser(bool)
{
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                  "/home",
                                                  tr("OpenStreetMap()"));
  if(fileName != nullptr)
  {
    Parser.parseXML(fileName.toStdString());
  }

  return fileName;
}

void GLWindow::outputToOBJ(bool)
{
  lonInterval = Parser.maxLon-Parser.minLon;
  latInterval = Parser.maxLat-Parser.minLat;
  roadWidth=0.1f;
  std::stringstream faces;
  verticeCount=1;

  Writer.clearOBJ();

  for( uint i = 0; i<Parser.ways.size(); i++)
  {
    for(uint j = 1; j<Parser.ways[i].nodesInWay.size(); j++)
    {
      //if all valid (e.g. not outliers) then push back node - NEED TO DO THIS STEP ON OUTPUT ie. WHEN POPULATING OBJ FILE
      if((Parser.nodes[Parser.ways[i].nodesInWay[j - 1]].nodeLat>=Parser.minLat)&&(Parser.nodes[Parser.ways[i].nodesInWay[j]].nodeLat<=Parser.maxLat)&&
         (Parser.nodes[Parser.ways[i].nodesInWay[j - 1]].nodeLon>=Parser.minLon)&&(Parser.nodes[Parser.ways[i].nodesInWay[j]].nodeLon<=Parser.maxLon))
      {
        X0 = ((Parser.nodes[Parser.ways[i].nodesInWay[j - 1]].nodeLat-Parser.minLat)/latInterval) * 100;
        Y0 = ((Parser.nodes[Parser.ways[i].nodesInWay[j - 1]].nodeLon-Parser.minLon)/lonInterval) * 100;
        X1 = ((Parser.nodes[Parser.ways[i].nodesInWay[j]].nodeLat-Parser.minLat)/latInterval) * 100;
        Y1 = ((Parser.nodes[Parser.ways[i].nodesInWay[j]].nodeLon-Parser.minLon)/lonInterval) * 100;

        /*
        //for different orientation testing - t-junction
        //for vertical roads
        if(j<=4)
        {
            // Test output to file
            std::stringstream ss;
            ss << "v " + (std::to_string(X0) + " 0.0 " + std::to_string(Y0) + "\n");
            toOBJ = ss.str();
            Writer.writeToOBJ(toOBJ);
            toOBJ.clear();

            //extra top node
            std::stringstream sss;
            Xtop0 = (((Parser.nodes[Parser.ways[i].nodesInWay[j - 1]].nodeLat-Parser.minLat)/latInterval) * 100);
            Ytop0 = (((Parser.nodes[Parser.ways[i].nodesInWay[j - 1]].nodeLon-Parser.minLon)/lonInterval) * 100)+roadWidth;
            sss << "v " + (std::to_string(Xtop0) + " 0.0 " + std::to_string(Ytop0) + "\n");
            toOBJ = sss.str();
            Writer.writeToOBJ(toOBJ);
            toOBJ.clear();

            //extra bottom node
            std::stringstream ssss;
            Xbot0 = (((Parser.nodes[Parser.ways[i].nodesInWay[j - 1]].nodeLat-Parser.minLat)/latInterval) * 100);
            Ybot0 = (((Parser.nodes[Parser.ways[i].nodesInWay[j - 1]].nodeLon-Parser.minLon)/lonInterval) * 100)-roadWidth;
            ssss << "v " + (std::to_string(Xbot0) + " 0.0 " + std::to_string(Ybot0) + "\n");
            toOBJ = ssss.str();
            Writer.writeToOBJ(toOBJ);
            toOBJ.clear();
        }
        //for horizontal roads
        else
        {
            // Test output to file
            std::stringstream ss;
            ss << "v " + (std::to_string(X0) + " 0.0 " + std::to_string(Y0) + "\n");
            toOBJ = ss.str();
            Writer.writeToOBJ(toOBJ);
            toOBJ.clear();

            //extra top node
            std::stringstream sss;
            Xtop0 = (((Parser.nodes[Parser.ways[i].nodesInWay[j - 1]].nodeLat-Parser.minLat)/latInterval) * 100)+roadWidth;
            Ytop0 = (((Parser.nodes[Parser.ways[i].nodesInWay[j - 1]].nodeLon-Parser.minLon)/lonInterval) * 100);
            sss << "v " + (std::to_string(Xtop0) + " 0.0 " + std::to_string(Ytop0) + "\n");
            toOBJ = sss.str();
            Writer.writeToOBJ(toOBJ);
            toOBJ.clear();

            //extra bottom node
            std::stringstream ssss;
            Xbot0 = (((Parser.nodes[Parser.ways[i].nodesInWay[j - 1]].nodeLat-Parser.minLat)/latInterval) * 100)-roadWidth;
            Ybot0 = (((Parser.nodes[Parser.ways[i].nodesInWay[j - 1]].nodeLon-Parser.minLon)/lonInterval) * 100);
            ssss << "v " + (std::to_string(Xbot0) + " 0.0 " + std::to_string(Ybot0) + "\n");
            toOBJ = ssss.str();
            Writer.writeToOBJ(toOBJ);
            toOBJ.clear();
        }*/

        // Test output to file
        std::stringstream ss;
        ss << "v " + (std::to_string(X0) + " 0.0 " + std::to_string(Y0) + "\n");
        toOBJ = ss.str();
        Writer.writeToOBJ(toOBJ);
        toOBJ.clear();
        verticeCount+=1;

        //extra top node
        std::stringstream sss;
        Xtop0 = (X0)+roadWidth;
        Ytop0 = (Y0);
        sss << "v " + (std::to_string(Xtop0) + " 0.0 " + std::to_string(Ytop0) + "\n");
        toOBJ = sss.str();
        Writer.writeToOBJ(toOBJ);
        toOBJ.clear();
        verticeCount+=1;

        //extra bottom node
        std::stringstream ssss;
        Xbot0 = (X0)-roadWidth;
        Ybot0 = (Y0);
        ssss << "v " + (std::to_string(Xbot0) + " 0.0 " + std::to_string(Ybot0) + "\n");
        toOBJ = ssss.str();
        Writer.writeToOBJ(toOBJ);
        toOBJ.clear();
        verticeCount+=1;
      }

    }

  }
  std::stringstream facePrep;
  facePrep << "s 1\nusemtl initialShadingGroup\n";
  toOBJ = facePrep.str();
  Writer.writeToOBJ(toOBJ);
  toOBJ.clear();
  //SINGLE ROAD IMPLEMENTATION OF FACE ASSIGNING USING TILING METHOD
  for(int k=1; k<verticeCount-3; k+=3)
  {
      faces << "f " + (std::to_string(k) + " " + std::to_string(k+3) + " " + std::to_string(k+4) + " " + std::to_string(k+1) + "\n");
  }
  for(int k=3; k<verticeCount-3; k+=3)
  {
      faces << "f " + (std::to_string(k) + " " + std::to_string(k+3) + " " + std::to_string(k+1) + " " + std::to_string(k-2) + "\n");
  }
  toOBJ = faces.str();
  Writer.writeToOBJ(toOBJ);
  toOBJ.clear();
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

    //NOTE LONDON INCLUDES UNDERGROUND INFO HENCE CRAZY LINES
    // OR IT MIGHT BE FLIGHT PATHS WE JUST DON'T KNOW
    // THIS MYSTERY RUNS DEEP
    // INDEED IT DOES
//    Parser.parseXML("data/NY");
}

void GLWindow::resizeGL(int _w, int _h)
{
    glViewport(0,0,_w,_h);
}

void GLWindow::slider(int _s)
{
  std::cout << _s << "\n";
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

void GLWindow::drawNodes()
{
  lonInterval = Parser.maxLon-Parser.minLon;
  latInterval = Parser.maxLat-Parser.minLat;

  glPointSize(3.0f);
  for(uint i = 0; i<=Parser.nodeRef; i++)
  {
    {
//        glPushMatrix();
//        glRotatef(90, 0.0, 0.0, 1.0);
//        glTranslatef(-50.0f,-50.0f,0.0f);
//        glBegin(GL_POINTS);
//          glColor3f(1.0,1.0,1.0);
//          //drawing nodes
//          glVertex3f(((Parser.nodes[i].nodeLat-Parser.minLat)/latInterval) * 100, ((Parser.nodes[i].nodeLon-Parser.minLon)/lonInterval) * 100, 0.0f);
//        glEnd();
//        glPopMatrix();
    }
  }
  for( uint i = 0; i<Parser.ways.size(); i++)
  {
    for(uint j = 1; j<Parser.ways[i].nodesInWay.size(); j++)
    {
      //if all valid (e.g. not outliers) then push back node - NEED TO DO THIS STEP ON OUTPUT ie. WHEN POPULATING OBJ FILE
      if((Parser.nodes[Parser.ways[i].nodesInWay[j - 1]].nodeLat>=Parser.minLat)&&(Parser.nodes[Parser.ways[i].nodesInWay[j]].nodeLat<=Parser.maxLat)&&
         (Parser.nodes[Parser.ways[i].nodesInWay[j - 1]].nodeLon>=Parser.minLon)&&(Parser.nodes[Parser.ways[i].nodesInWay[j]].nodeLon<=Parser.maxLon))
      {
        X0 = ((Parser.nodes[Parser.ways[i].nodesInWay[j - 1]].nodeLat-Parser.minLat)/latInterval) * 100;
        Y0 = ((Parser.nodes[Parser.ways[i].nodesInWay[j - 1]].nodeLon-Parser.minLon)/lonInterval) * 100;
        X1 = ((Parser.nodes[Parser.ways[i].nodesInWay[j]].nodeLat-Parser.minLat)/latInterval) * 100;
        Y1 = ((Parser.nodes[Parser.ways[i].nodesInWay[j]].nodeLon-Parser.minLon)/lonInterval) * 100;

        glPushMatrix();
          glRotatef(90.0, 0.0, 0.0, 1.0);
          glTranslatef(-50.0f,-50.0f,0.0f);
          glBegin(GL_LINES);
            glColor3f(1.0,1.0,1.0);
            //drawing ways
            glVertex3f(X0, Y0, 0.0f);

            glVertex3f(X1, Y1, 0.0f);


          glEnd();
        glPopMatrix();

      }


        //std::cout<<((Parser.nodes[Parser.ways[i].nodesInWay[j]].nodeLat-Parser.minLat)/latInterval) * 100<<"\n";

    }

  }
}
