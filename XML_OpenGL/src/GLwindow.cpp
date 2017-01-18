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
    Parser.checkIntersections();
  }

  return fileName;
}

void GLWindow::outputToOBJ(bool)
{
    lonInterval = Parser.maxLon-Parser.minLon;
    latInterval = Parser.maxLat-Parser.minLat;
    roadWidth=1.0f;
    std::stringstream faces;
    verticeCount=1;
    float verticeCountWay;
    float nodeCount=0;

    Writer.clearOBJ();

    for( uint i = 0; i<Parser.Network.ways.size(); i++)
    {
        verticeCountWay=1;
        for(uint j = 1; j<Parser.Network.ways[i].nodesInWay.size(); j++)
        {
            nodeCount+=1;
            //if all valid (e.g. not outliers) then push back node - NEED TO DO THIS STEP ON OUTPUT ie. WHEN POPULATING OBJ FILE
            //if((Parser.nodes[Parser.ways[i].nodesInWay[j - 1].nodeRef].nodeLat>=Parser.minLat)&&(Parser.nodes[Parser.ways[i].nodesInWay[j].nodeRef].nodeLat<=Parser.maxLat)&&
              // (Parser.nodes[Parser.ways[i].nodesInWay[j - 1].nodeRef].nodeLon>=Parser.minLon)&&(Parser.nodes[Parser.ways[i].nodesInWay[j].nodeRef].nodeLon<=Parser.maxLon))
            //{
                //only if theres enough nodes in a way to make a face - theres a problem here with outliers, the original way may well
                //have more than 1 node but when it goes through the next check not all nodes may make it through
                if(Parser.Network.ways[i].nodesInWay.size()>1)
                {
                    //NEW SYSTEM, CALCULATES HOW MUCH ROAD WIDTH TO ADD IN HORIZONTAL AND VERTICAL BASED ON DIFFERENCE IN LAT AND LONG BETWEEN TWO NODES
                    //for node first only - first two nodes will have same scalar affecting them, first two nodes setup occuring here
                    if(j==1)
                    {
                        std::stringstream name;
                        name << "#" << Parser.Network.ways[i].name << "\n";
                        toOBJ = name.str();
                        Writer.writeToOBJ(toOBJ);
                        toOBJ.clear();
                        X0 = ((Parser.Network.nodes[Parser.Network.ways[i].nodesInWay[j - 1].nodeRef].nodeLat-Parser.minLat)/latInterval) * 100;
                        Y0 = ((Parser.Network.nodes[Parser.Network.ways[i].nodesInWay[j - 1].nodeRef].nodeLon-Parser.minLon)/lonInterval) * 100;
                        X1 = ((Parser.Network.nodes[Parser.Network.ways[i].nodesInWay[j].nodeRef].nodeLat-Parser.minLat)/latInterval) * 100;
                        Y1 = ((Parser.Network.nodes[Parser.Network.ways[i].nodesInWay[j].nodeRef].nodeLon-Parser.minLon)/lonInterval) * 100;

                        float latDiff = X1-X0;
                        float lonDiff = Y1-Y0;
                        if(latDiff<0)
                        {
                            latDiff*=-1;
                        }
                        if(lonDiff<0)
                        {
                            lonDiff*=-1;
                        }
                        float sum =latDiff+lonDiff;

                        // Test output to file
                        std::stringstream orig;
                        orig << "v " + (std::to_string(X0) + " 0.0 " + std::to_string(Y0) + "\n");
                        toOBJ = orig.str();
                        Writer.writeToOBJ(toOBJ);
                        toOBJ.clear();
                        verticeCount+=1;
                        verticeCountWay+=1;

                        //extra top node
                        std::stringstream top;
                        Xtop0 = X0+(roadWidth*lonDiff/sum);
                        Ytop0 = Y0+(roadWidth*latDiff/sum);
                        top << "v " + (std::to_string(Xtop0) + " 0.0 " + std::to_string(Ytop0) + "\n");
                        toOBJ = top.str();
                        Writer.writeToOBJ(toOBJ);
                        toOBJ.clear();
                        verticeCount+=1;
                        verticeCountWay+=1;

                        //extra bottom node
                        std::stringstream bot;
                        Xbot0 = X0-(roadWidth*lonDiff/sum);
                        Ybot0 = Y0-(roadWidth*latDiff/sum);
                        bot << "v " + (std::to_string(Xbot0) + " 0.0 " + std::to_string(Ybot0) + "\n");
                        toOBJ = bot.str();
                        Writer.writeToOBJ(toOBJ);
                        toOBJ.clear();
                        verticeCount+=1;
                        verticeCountWay+=1;

                        // Test output to file
                        std::stringstream orig1;
                        orig1 << "v " + (std::to_string(X1) + " 0.0 " + std::to_string(Y1) + "\n");
                        toOBJ = orig1.str();
                        Writer.writeToOBJ(toOBJ);
                        toOBJ.clear();
                        verticeCount+=1;
                        verticeCountWay+=1;

                        //extra top node
                        std::stringstream top1;
                        Xtop0 = X1+(roadWidth*lonDiff/sum);
                        Ytop0 = Y1+(roadWidth*latDiff/sum);
                        top1 << "v " + (std::to_string(Xtop0) + " 0.0 " + std::to_string(Ytop0) + "\n");
                        toOBJ = top1.str();
                        Writer.writeToOBJ(toOBJ);
                        toOBJ.clear();
                        verticeCount+=1;
                        verticeCountWay+=1;

                        //extra bottom node
                        std::stringstream bot1;
                        Xbot0 = X1-(roadWidth*lonDiff/sum);
                        Ybot0 = Y1-(roadWidth*latDiff/sum);
                        bot1 << "v " + (std::to_string(Xbot0) + " 0.0 " + std::to_string(Ybot0) + "\n");
                        toOBJ = bot1.str();
                        Writer.writeToOBJ(toOBJ);
                        toOBJ.clear();
                        verticeCount+=1;
                        verticeCountWay+=1;
                    }
                    //must skip second turn as the set of beginning nodes carried out above, for this the scaling is calculated using node behind current
                    else if(j>2)
                    {
                        //current node
                        X1 = ((Parser.Network.nodes[Parser.Network.ways[i].nodesInWay[j - 1].nodeRef].nodeLat-Parser.minLat)/latInterval) * 100;
                        Y1 = ((Parser.Network.nodes[Parser.Network.ways[i].nodesInWay[j - 1].nodeRef].nodeLon-Parser.minLon)/lonInterval) * 100;
                        //prev node
                        X0 = ((Parser.Network.nodes[Parser.Network.ways[i].nodesInWay[j - 2].nodeRef].nodeLat-Parser.minLat)/latInterval) * 100;
                        Y0 = ((Parser.Network.nodes[Parser.Network.ways[i].nodesInWay[j - 2].nodeRef].nodeLon-Parser.minLon)/lonInterval) * 100;

                        float latDiff = X1-X0;
                        float lonDiff = Y1-Y0;
                        if(latDiff<0)
                        {
                            latDiff*=-1;
                        }
                        if(lonDiff<0)
                        {
                            lonDiff*=-1;
                        }
                        float sum =latDiff+lonDiff;

                        // Test output to file
                        std::stringstream ss;
                        ss << "v " + (std::to_string(X1) + " 0.0 " + std::to_string(Y1) + "\n");
                        toOBJ = ss.str();
                        Writer.writeToOBJ(toOBJ);
                        toOBJ.clear();
                        verticeCount+=1;
                        verticeCountWay+=1;

                        //extra top node
                        std::stringstream sss;
                        Xtop0 = X1+(roadWidth*lonDiff/sum);
                        Ytop0 = Y1+(roadWidth*latDiff/sum);
                        sss << "v " + (std::to_string(Xtop0) + " 0.0 " + std::to_string(Ytop0) + "\n");
                        toOBJ = sss.str();
                        Writer.writeToOBJ(toOBJ);
                        toOBJ.clear();
                        verticeCount+=1;
                        verticeCountWay+=1;

                        //extra bottom node
                        std::stringstream ssss;
                        Xbot0 = X1-(roadWidth*lonDiff/sum);
                        Ybot0 = Y1-(roadWidth*latDiff/sum);
                        ssss << "v " + (std::to_string(Xbot0) + " 0.0 " + std::to_string(Ybot0) + "\n");
                        toOBJ = ssss.str();
                        Writer.writeToOBJ(toOBJ);
                        toOBJ.clear();
                        verticeCount+=1;
                        verticeCountWay+=1;
                    }
                }
            }
            //SINGLE ROAD IMPLEMENTATION OF FACE ASSIGNING  - TRYING TO GET IT WORKING WITH MULTIPLE WAYS
            for(int k=(verticeCount-verticeCountWay)+1; k<verticeCount-3; k+=3)
            {
                faces << "f " + (std::to_string(k) + " " + std::to_string(k+3) + " " + std::to_string(k+4) + " " + std::to_string(k+1) + "\n");
            }
            for(int k=(verticeCount-verticeCountWay)+3; k<verticeCount-3; k+=3)
            {
                faces << "f " + (std::to_string(k) + " " + std::to_string(k+3) + " " + std::to_string(k+1) + " " + std::to_string(k-2) + "\n");
            }
        //}
    }
    std::stringstream facePrep;
    facePrep << "s "+ std::to_string(1) + "\n";
    facePrep << "usemtl initialShadingGroup\n";
    toOBJ = facePrep.str();
    Writer.writeToOBJ(toOBJ);
    toOBJ.clear();

    toOBJ = faces.str();
    Writer.writeToOBJ(toOBJ);
    faces.clear();
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

  for( uint i = 0; i<Parser.Network.ways.size(); i++)
  {
    for(uint j = 1; j<Parser.Network.ways[i].nodesInWay.size(); j++)
    {
      //if all valid (e.g. not outliers) then push back node
      if((Parser.Network.nodes[Parser.Network.ways[i].nodesInWay[j - 1].nodeRef].nodeLat>=Parser.minLat)&&(Parser.Network.nodes[Parser.Network.ways[i].nodesInWay[j].nodeRef].nodeLat<=Parser.maxLat)&&
         (Parser.Network.nodes[Parser.Network.ways[i].nodesInWay[j - 1].nodeRef].nodeLon>=Parser.minLon)&&(Parser.Network.nodes[Parser.Network.ways[i].nodesInWay[j].nodeRef].nodeLon<=Parser.maxLon))
      {
//        std::cout<<Parser.ways[i].nodesInWay[j - 1].nodeRef<<"\n";
        X0 = ((Parser.Network.nodes[Parser.Network.ways[i].nodesInWay[j - 1].nodeRef].nodeLat-Parser.minLat)/latInterval) * 100;
        Y0 = ((Parser.Network.nodes[Parser.Network.ways[i].nodesInWay[j - 1].nodeRef].nodeLon-Parser.minLon)/lonInterval) * 100;
        X1 = ((Parser.Network.nodes[Parser.Network.ways[i].nodesInWay[j].nodeRef].nodeLat-Parser.minLat)/latInterval) * 100;
        Y1 = ((Parser.Network.nodes[Parser.Network.ways[i].nodesInWay[j].nodeRef].nodeLon-Parser.minLon)/lonInterval) * 100;

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

void GLWindow::createNewNetwork(bool)
{
  for(uint i = 0; i < Parser.Network.nodes.size(); i++)
  {
    Parser.Network.nodes[i].inNewNetwork = false;
  }
  float intersectionUseAgain = 0.0f;
  NewNetwork.currentNode = Parser.Network.nodes[0];
  NewNetwork.currentWay.nodesInWay.push_back(Parser.Network.nodes[0]);
  NewNetwork.currentNode.inNewNetwork = true;
  NewNetwork.currentNode = Parser.Network.nodes[1];
  NewNetwork.currentWay.nodesInWay.push_back(Parser.Network.nodes[1]);
  bool unusedNodes = true;
  node prevNode = Parser.Network.nodes[0];
  while(unusedNodes == true)
  {
    unusedNodes = false;
    for(uint j = 0; j <Parser.Network.nodes.size(); j++)
    {
      if(Parser.Network.nodes[j].inNewNetwork == true)
      {
        continue;
      }
      else
      {
        NewNetwork.currentNode.inNewNetwork = true;
        unusedNodes = true;
        node temp = NewNetwork.currentNode;
        NewNetwork.currentNode = findNextnode(NewNetwork.currentNode, prevNode);
        prevNode = temp;
        NewNetwork.currentWay.nodesInWay.push_back(NewNetwork.currentNode);
      }
    }
  }
}

node GLWindow::findNextnode(node CurrentNode, node PrevNode)
{
  node temp[5];
  float len;
  float tempLen[5];
  for(uint i = 0; i < Parser.Network.nodes.size(); i++)
  {
    bool isInWay = false;
    if(Parser.Network.nodes[i].nodeRef != CurrentNode.nodeRef)
    {
      for(uint x = 0; x < NewNetwork.currentWay.nodesInWay.size(); x++)
      {
        if(Parser.Network.nodes[i].nodeRef == NewNetwork.currentWay.nodesInWay[x].nodeRef)
        {
          isInWay = true;
          break;
        }
      }
      if(isInWay == true)
      {
        isInWay = false;
        break;
      }
      len = (sqrt((CurrentNode.nodeLat - Parser.Network.nodes[i].nodeLat)*(CurrentNode.nodeLat - Parser.Network.nodes[i].nodeLat) + (CurrentNode.nodeLon - Parser.Network.nodes[i].nodeLon)*(CurrentNode.nodeLon - Parser.Network.nodes[i].nodeLon)));
      for(int j = 0; j < 5; j++)
      {
        tempLen[j] = (sqrt((CurrentNode.nodeLat - temp[j].nodeLat)*(CurrentNode.nodeLat - temp[j].nodeLat) + (CurrentNode.nodeLon - temp[j].nodeLon)*(CurrentNode.nodeLon - temp[j].nodeLon)));
        if(len < tempLen[j])
        {
          for(int y = j; y < 5; y++)
          {
            temp[y+1] = temp[y];
          }
          temp[j] = Parser.Network.nodes[i];
          break;

        }
      }
    }
  }
  for(uint k = 0; k < 5; k++)
  {
    if(NewNetwork.nodes[temp[k].nodeRef].numIntersections == 4)
    {
      continue;
    }
    float mag = sqrt((CurrentNode.nodeLat - PrevNode.nodeLat)*(CurrentNode.nodeLat - PrevNode.nodeLat) + (CurrentNode.nodeLon - PrevNode.nodeLon)*(CurrentNode.nodeLon - PrevNode.nodeLon));
    float tNormLat = (CurrentNode.nodeLat - temp[k].nodeLat) / tempLen[k];
    float tNormLon = (CurrentNode.nodeLon - temp[k].nodeLon) / tempLen[k];
    float cNormLat = (CurrentNode.nodeLat - PrevNode.nodeLat) / mag;
    float cNormLon = (CurrentNode.nodeLon - PrevNode.nodeLon) / mag;

    if(acos(tNormLat * cNormLat + tNormLon * cNormLon) < 0.523599)
    {
      continue;
    }

    // TODO: Check if this would cross over existing road

    return temp[k];

  }

  exit(0);
}
