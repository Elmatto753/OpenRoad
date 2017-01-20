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
    m_y=0.0f;
    //NEED TO CHANGE TO 0, MEANS DEFAULT WILL BE TO HAVE THE NEW SYSTEM SELECTED FOR DRAWING
    originalSystem=1;
    nullNode.isNull = true;
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
    Parser.unfinishedNodes();
  }

  //emit imasignal();

  return fileName;
}

void GLWindow::OBJfill(network _Network)
{
    lonInterval = Parser.maxLon-Parser.minLon;
    latInterval = Parser.maxLat-Parser.minLat;
    roadWidth=1.0f;
    std::stringstream faces;
    verticeCount=1;
    float verticeCountWay;
    float nodeCount=0;

    Writer.clearOBJ();

    for( uint i = 0; i<_Network.ways.size(); i++)
    {
        verticeCountWay=1;
        for(uint j = 1; j<_Network.ways[i].nodesInWay.size(); j++)
        {
            nodeCount+=1;
            //if all valid (e.g. not outliers) then push back node - NEED TO DO THIS STEP ON OUTPUT ie. WHEN POPULATING OBJ FILE
            //if((Parser.nodes[Parser.ways[i].nodesInWay[j - 1].nodeRef].nodeLat>=Parser.minLat)&&(Parser.nodes[Parser.ways[i].nodesInWay[j].nodeRef].nodeLat<=Parser.maxLat)&&
              // (Parser.nodes[Parser.ways[i].nodesInWay[j - 1].nodeRef].nodeLon>=Parser.minLon)&&(Parser.nodes[Parser.ways[i].nodesInWay[j].nodeRef].nodeLon<=Parser.maxLon))
            //{
                //only if theres enough nodes in a way to make a face - theres a problem here with outliers, the original way may well
                //have more than 1 node but when it goes through the next check not all nodes may make it through
                if(_Network.ways[i].nodesInWay.size()>1)
                {
                    //NEW SYSTEM, CALCULATES HOW MUCH ROAD WIDTH TO ADD IN HORIZONTAL AND VERTICAL BASED ON DIFFERENCE IN LAT AND LONG BETWEEN TWO NODES
                    //for node first only - first two nodes will have same scalar affecting them, first two nodes setup occuring here
                    if(j==1)
                    {
                        std::stringstream name;
                        name << "#" << _Network.ways[i].name << "\n";
                        toOBJ = name.str();
                        Writer.writeToOBJ(toOBJ);
                        toOBJ.clear();
                        X0 = ((_Network.nodes[_Network.ways[i].nodesInWay[j - 1].nodeRef].nodeLat-Parser.minLat)/latInterval) * 100;
                        Y0 = ((_Network.nodes[_Network.ways[i].nodesInWay[j - 1].nodeRef].nodeLon-Parser.minLon)/lonInterval) * 100;
                        X1 = ((_Network.nodes[_Network.ways[i].nodesInWay[j].nodeRef].nodeLat-Parser.minLat)/latInterval) * 100;
                        Y1 = ((_Network.nodes[_Network.ways[i].nodesInWay[j].nodeRef].nodeLon-Parser.minLon)/lonInterval) * 100;

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
                        X1 = ((_Network.nodes[_Network.ways[i].nodesInWay[j - 1].nodeRef].nodeLat-Parser.minLat)/latInterval) * 100;
                        Y1 = ((_Network.nodes[_Network.ways[i].nodesInWay[j - 1].nodeRef].nodeLon-Parser.minLon)/lonInterval) * 100;
                        //prev node
                        X0 = ((_Network.nodes[_Network.ways[i].nodesInWay[j - 2].nodeRef].nodeLat-Parser.minLat)/latInterval) * 100;
                        Y0 = ((_Network.nodes[_Network.ways[i].nodesInWay[j - 2].nodeRef].nodeLon-Parser.minLon)/lonInterval) * 100;

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

void GLWindow::useOriginalNetwork(bool)
{
    originalSystem=1;
}

void GLWindow::useNewNetwork(bool)
{
    originalSystem=0;
}

void GLWindow::outputToOBJ(bool)
{
    if(originalSystem==1)
    {
        OBJfill(Parser.Network);
    }
    else if(originalSystem==0)
    {
        OBJfill(Parser.NewNetwork);
    }
}

void GLWindow::initializeGL()
{
    glClearColor(0.6,  0.6, 0.6, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(75,float(width()/height()),0.1,1000);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_NORMALIZE);
    glLoadIdentity();
    gluLookAt(0,0,-120,0,0,0,0,1,0);
    startTimer(1);
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

    if(originalSystem==1)
    {
        drawNodes(Parser.Network);
    }
    else if(originalSystem==0)
    {
        drawNodes(Parser.NewNetwork);
    }

}

void GLWindow::timerEvent(QTimerEvent *)
{
    update();
}

void GLWindow::drawNodes(network _Network)
{
  lonInterval = Parser.maxLon-Parser.minLon;
  latInterval = Parser.maxLat-Parser.minLat;

  glPointSize(3.0f);

  for( uint i = 0; i<_Network.ways.size(); i++)
  {
    for(uint j = 1; j<_Network.ways[i].nodesInWay.size(); j++)
    {
      //if all valid (e.g. not outliers) then push back node
//      if((_Network.nodes[_Network.ways[i].nodesInWay[j - 1].nodeRef].nodeLat>=Parser.minLat)&&(_Network.nodes[_Network.ways[i].nodesInWay[j].nodeRef].nodeLat<=Parser.maxLat)&&
//         (_Network.nodes[_Network.ways[i].nodesInWay[j - 1].nodeRef].nodeLon>=Parser.minLon)&&(_Network.nodes[_Network.ways[i].nodesInWay[j].nodeRef].nodeLon<=Parser.maxLon))
//      {
        X0 = ((_Network.nodes[_Network.ways[i].nodesInWay[j - 1].nodeRef].nodeLat-Parser.minLat)/latInterval) * 100;
        Y0 = ((_Network.nodes[_Network.ways[i].nodesInWay[j - 1].nodeRef].nodeLon-Parser.minLon)/lonInterval) * 100;
        X1 = ((_Network.nodes[_Network.ways[i].nodesInWay[j].nodeRef].nodeLat-Parser.minLat)/latInterval) * 100;
        Y1 = ((_Network.nodes[_Network.ways[i].nodesInWay[j].nodeRef].nodeLon-Parser.minLon)/lonInterval) * 100;

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

//      }
    }

  }
}

void GLWindow::analyseNetwork(network Network)
{
  uint totIntersections = 0;
  uint maxIntersections = 0;
  uint minIntersections = 0;
  uint angleCount = 0;
  float totAngle = 0.0f;
  maxAngle = 0.0f;
  minAngle = 2 * M_PI;
  minDistance = 1.0f;
  maxDistance = 0.0f;
  uint distDivisor = 0;
  float distance=0.0f;

  for(uint i = 0; i < Network.ways.size(); i++)
  {
    if(Network.ways[i].intersections.size() > maxIntersections)
    {
      maxIntersections = Network.ways[i].intersections.size();
    }
    totIntersections += Network.ways[i].intersections.size();

    for(uint j = 1; j < Network.ways[i].nodesInWay.size() - 1; j++)
    {
      float magToPrev = sqrt((Network.ways[i].nodesInWay[j].nodeLat - Network.ways[i].nodesInWay[j-1].nodeLat)*(Network.ways[i].nodesInWay[j].nodeLat - Network.ways[i].nodesInWay[j-1].nodeLat) +
                             (Network.ways[i].nodesInWay[j].nodeLon - Network.ways[i].nodesInWay[j-1].nodeLon)*(Network.ways[i].nodesInWay[j].nodeLon - Network.ways[i].nodesInWay[j-1].nodeLon));
      float magToNext = sqrt((Network.ways[i].nodesInWay[j+1].nodeLat - Network.ways[i].nodesInWay[j].nodeLat)*(Network.ways[i].nodesInWay[j+1].nodeLat - Network.ways[i].nodesInWay[j].nodeLat) +
                             (Network.ways[i].nodesInWay[j+1].nodeLon - Network.ways[i].nodesInWay[j].nodeLon)*(Network.ways[i].nodesInWay[j+1].nodeLon - Network.ways[i].nodesInWay[j].nodeLon));
      float prevNormLat = (Network.ways[i].nodesInWay[j].nodeLat - Network.ways[i].nodesInWay[j-1].nodeLat) / magToPrev;
      float prevNormLon = (Network.ways[i].nodesInWay[j].nodeLon - Network.ways[i].nodesInWay[j-1].nodeLon) / magToPrev;
      float curNormLat = (Network.ways[i].nodesInWay[j].nodeLat - Network.ways[i].nodesInWay[j+1].nodeLat) / magToNext;
      float curNormLon = (Network.ways[i].nodesInWay[j].nodeLon - Network.ways[i].nodesInWay[j+1].nodeLon) / magToNext;
      float angle = acos(prevNormLat * curNormLat + prevNormLon * curNormLon);
      totAngle += angle;
      angleCount+=1;
      //updating min and max angle if bigger or smaller is found
      if(angle > maxAngle)
      {
        maxAngle = angle;
      }
      if(angle < minAngle)
      {
        minAngle = angle;
      }
      if(magToPrev > maxDistance)
      {
        maxDistance = magToPrev;
      }
      if(magToPrev < minDistance)
      {
        minDistance = magToPrev;
      }
      distance+=magToPrev;
    }
  }

  avgIntersections = totIntersections / Network.ways.size();
  avgNodes = Network.nodes.size() / Network.ways.size();
  avgDistance = distance/angleCount;
  avgAngle = totAngle / angleCount;
  std::cout<<"\navgInt: "<<avgIntersections<<" avgNodes: "<<avgNodes<<" avgDistance: "<<avgDistance<<"\n";
  std::cout<<"mindist: "<<minDistance<<" maxdist: "<<maxDistance<<"\n";
  std::cout<<"avgAngle: "<<avgAngle<<" minAngle: "<<minAngle<<" maxAngle: "<<maxAngle<<"\n";

}

//using values analyzed from original graph with random permutations - SORRY IT CRASHES
void GLWindow::extendNetwork()
{
  uint node_Ref = Parser.Network.nodes.size();
  uint way_Ref;
  uint numberOfNodes;
  //keep track of how many nodes and intersection points already used
  uint nodesInWay;
  uint interInWay;
  bool intersectPoint=false;

  //start checking for an unfinished node
  for( uint i = 0; i<Parser.NewNetwork.ways.size(); i++)
  {
    for(uint j = 1; j<Parser.NewNetwork.ways[i].nodesInWay.size(); j++)
    {
      //need to be editing the latest way added, so this should always update itself when a way is pushed back
      way_Ref=Parser.NewNetwork.ways.size();//potentially needs to be plus 1
      //when one is reached
      if(Parser.NewNetwork.ways[i].nodesInWay[j].isUnfinished==true)
      {
        Parser.NewNetwork.ways[i].nodesInWay[j].isUnfinished=false;
        //reset for next way used to keep track of how many nodes and intersections already added
        nodesInWay=0;
        interInWay=0;
        //push back new way, generate random number of intersections and nodes for this new way to have
        way emptyWay;
        Parser.NewNetwork.ways.push_back(emptyWay);

        int randomNodes = rand() % 11 + (-5);
        int randomIntersection = rand() % 2 + (-1);
        float randomLength = minDistance + ( (((float) rand()) / (float) RAND_MAX) * (maxDistance - minDistance) );
        float randomAngle = minAngle + ( (((float) rand()) / (float) RAND_MAX) * (maxAngle - minAngle) );
        //length = avgDistance + ((-0.5 + ((((float) rand()) / (float) RAND_MAX) )) * randomLength);
        numberOfNodes=avgNodes+randomNodes;
        uint numberOfIntersections=avgIntersections+randomIntersection;


        //push back nodes one at a time then for each node (loop through the number of nodes in this new way)
        for(uint k=0; k<numberOfNodes; k++)
        {
          node emptyNode;

          Parser.NewNetwork.ways[way_Ref].nodesInWay.push_back(emptyNode);

          node_Ref+=1;
          //for first node it should always equal position of original unfinished node and shouldn't be an intersection
          if(k==0)
          {
            Parser.NewNetwork.ways[way_Ref].nodesInWay[k].nodeLat=Parser.NewNetwork.ways[i].nodesInWay[j].nodeLat;
            Parser.NewNetwork.ways[way_Ref].nodesInWay[k].nodeLon=Parser.NewNetwork.ways[i].nodesInWay[j].nodeLon;

            Parser.NewNetwork.ways[way_Ref].nodesInWay[k].isIntersection=false;

            nodesInWay+=1;
          }
          else
          {
            //NODE NEW POSITION CALCULATIONS - NEED TO WORK OUT BASED ON AVERAGE ANGLE AND AVERAGE DISTANCE
            float lat=0.0f, lon=0.0f;

            lat = Parser.NewNetwork.ways[way_Ref].nodesInWay[k-1].nodeLat + randomLength * cos(randomAngle);
            lon = Parser.NewNetwork.ways[way_Ref].nodesInWay[k-1].nodeLon + randomLength * cos((M_PI/2) - randomAngle);
            //std::cout<<"lat: "<<lat<<" lon: "<<lon<<"\n";

            //calcualte node position based on average angle (to give vector) and average distance to give final lat and long

            Parser.NewNetwork.ways[way_Ref].nodesInWay[k].nodeLat=lat;
            Parser.NewNetwork.ways[way_Ref].nodesInWay[k].nodeLon=lon;

            //INTERSECTION POINT DECIDING
            //if intersection quota has already been filled for this way
            if(interInWay==numberOfIntersections)
            {
                intersectPoint=false;
            }
            //already filled up normal node quota - has to be an intersect Node
            else if(nodesInWay==(numberOfNodes-numberOfIntersections))
            {
                intersectPoint=true;
            }
            //neither quota filled up, random choice of what the decision will be
            else
            {
                int randomiser = rand() % 2;
                if(randomiser==0)
                {
                    intersectPoint=true;
                }
                else if(randomiser==1)
                {
                    intersectPoint=false;
                }
            }

            //decide whether node is intersection or not
            if(intersectPoint==true)
            {
                //Parser.NewNetwork.currentNode.isIntersection=true;
                Parser.NewNetwork.ways[way_Ref].nodesInWay[k].isIntersection=true;
                interInWay+=1;
            }
            else if(intersectPoint==false)
            {
                //Parser.NewNetwork.currentNode.isIntersection=false;
                Parser.NewNetwork.ways[way_Ref].nodesInWay[k].isIntersection=false;
                nodesInWay+=1;
            }
          }

          //finally update node_ref count
          Parser.NewNetwork.ways[way_Ref].nodesInWay[k].nodeRef=node_Ref;
          Parser.NewNetwork.nodes.push_back(Parser.NewNetwork.ways[way_Ref].nodesInWay[k]);
        }
      }
    }
  }
  //std::cout<<"\nNetwork size: "<<Parser.Network.ways.size()<<" NewNetwork size: "<<Parser.NewNetwork.ways.size()<<"\n";
}

void GLWindow::createNewNetwork(bool)
{
  //first find info about current network
  analyseNetwork(Parser.Network);
  //step 2 - extend network
  extendNetwork();
  originalSystem=0;
}
