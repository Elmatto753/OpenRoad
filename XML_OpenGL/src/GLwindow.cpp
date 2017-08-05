#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif

#include <QKeyEvent>
#include <QGuiApplication>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <random>
#include "GLWindow.h"

GLWindow::GLWindow(QWidget *_parent) :
  QOpenGLWidget(_parent)
{
    m_y=0.0f;
    //NEED TO CHANGE TO 0, MEANS DEFAULT WILL BE TO HAVE THE NEW SYSTEM SELECTED FOR DRAWING
    m_originalSystem=1;
}

GLWindow::~GLWindow()
{

}

//by default file browser will open user's home directory, function then calls parser
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
    return fileName;
}

//Generates vertices and face information and stores it in map.osm in output folder
void GLWindow::OBJfill(network _Network)
{
    m_lonInterval = Parser.m_maxLon-Parser.m_minLon;
    m_latInterval = Parser.m_maxLat-Parser.m_minLat;
    m_roadWidth=1.0f;
    std::stringstream faces;
    m_verticeCount=1;
    float nodeCount=0;

    Writer.clearOBJ();

    for( unsigned int i = 0; i<_Network.ways.size(); i++)
    {
        m_verticeCountWay=1;
        for(unsigned int j = 1; j<_Network.ways[i].nodesInWay.size(); j++)
        {
            nodeCount+=1;
            //only if theres enough nodes in a way to make a face, need two original nodes
            if(_Network.ways[i].nodesInWay.size()>1)
            {
                //CALCULATES HOW MUCH ROAD WIDTH TO ADD IN HORIZONTAL AND VERTICAL BASED ON DIFFERENCE IN LAT AND LONG BETWEEN TWO NODES
                //for node first only - first two nodes will have same scalar affecting them, first two nodes setup occuring here
                if(j==1)
                {
                    std::stringstream name;
                    name << "#" << _Network.ways[i].name << "\n";
                    m_toOBJ = name.str();
                    Writer.writeToOBJ(m_toOBJ);
                    m_toOBJ.clear();
                    m_X0 = ((_Network.nodes[_Network.ways[i].nodesInWay[j - 1].nodeRef].nodeLat-Parser.m_minLat)/m_latInterval) * 100;
                    m_Y0 = ((_Network.nodes[_Network.ways[i].nodesInWay[j - 1].nodeRef].nodeLon-Parser.m_minLon)/m_lonInterval) * 100;
                    m_X1 = ((_Network.nodes[_Network.ways[i].nodesInWay[j].nodeRef].nodeLat-Parser.m_minLat)/m_latInterval) * 100;
                    m_Y1 = ((_Network.nodes[_Network.ways[i].nodesInWay[j].nodeRef].nodeLon-Parser.m_minLon)/m_lonInterval) * 100;

                    float latDiff = m_X1-m_X0;
                    float lonDiff = m_Y1-m_Y0;
                    if(latDiff<0)
                    {
                        latDiff*=-1;
                    }
                    if(lonDiff<0)
                    {
                        lonDiff*=-1;
                    }
                    float sum =latDiff+lonDiff;

                    //original node
                    std::stringstream orig;
                    orig << "v " + (std::to_string(m_X0) + " 0.0 " + std::to_string(m_Y0) + "\n");
                    m_toOBJ = orig.str();
                    Writer.writeToOBJ(m_toOBJ);
                    m_toOBJ.clear();
                    m_verticeCount+=1;
                    m_verticeCountWay+=1;

                    //extra top node
                    std::stringstream top;
                    m_Xtop0 = m_X0+(m_roadWidth*lonDiff/sum);
                    m_Ytop0 = m_Y0+(m_roadWidth*latDiff/sum);
                    top << "v " + (std::to_string(m_Xtop0) + " 0.0 " + std::to_string(m_Ytop0) + "\n");
                    m_toOBJ = top.str();
                    Writer.writeToOBJ(m_toOBJ);
                    m_toOBJ.clear();
                    m_verticeCount+=1;
                    m_verticeCountWay+=1;

                    //extra bottom node
                    std::stringstream bot;
                    m_Xbot0 = m_X0-(m_roadWidth*lonDiff/sum);
                    m_Ybot0 = m_Y0-(m_roadWidth*latDiff/sum);
                    bot << "v " + (std::to_string(m_Xbot0) + " 0.0 " + std::to_string(m_Ybot0) + "\n");
                    m_toOBJ = bot.str();
                    Writer.writeToOBJ(m_toOBJ);
                    m_toOBJ.clear();
                    m_verticeCount+=1;
                    m_verticeCountWay+=1;

                    //original node - next node
                    std::stringstream orig1;
                    orig1 << "v " + (std::to_string(m_X1) + " 0.0 " + std::to_string(m_Y1) + "\n");
                    m_toOBJ = orig1.str();
                    Writer.writeToOBJ(m_toOBJ);
                    m_toOBJ.clear();
                    m_verticeCount+=1;
                    m_verticeCountWay+=1;

                    //extra top node - next node
                    std::stringstream top1;
                    m_Xtop0 = m_X1+(m_roadWidth*lonDiff/sum);
                    m_Ytop0 = m_Y1+(m_roadWidth*latDiff/sum);
                    top1 << "v " + (std::to_string(m_Xtop0) + " 0.0 " + std::to_string(m_Ytop0) + "\n");
                    m_toOBJ = top1.str();
                    Writer.writeToOBJ(m_toOBJ);
                    m_toOBJ.clear();
                    m_verticeCount+=1;
                    m_verticeCountWay+=1;

                    //extra bottom node - next node
                    std::stringstream bot1;
                    m_Xbot0 = m_X1-(m_roadWidth*lonDiff/sum);
                    m_Ybot0 = m_Y1-(m_roadWidth*latDiff/sum);
                    bot1 << "v " + (std::to_string(m_Xbot0) + " 0.0 " + std::to_string(m_Ybot0) + "\n");
                    m_toOBJ = bot1.str();
                    Writer.writeToOBJ(m_toOBJ);
                    m_toOBJ.clear();
                    m_verticeCount+=1;
                    m_verticeCountWay+=1;
                }
                //must skip second turn as the set of beginning nodes carried out above, for this the scaling is calculated using node behind current
                else if(j>2)
                {
                    //current node
                    m_X1 = ((_Network.nodes[_Network.ways[i].nodesInWay[j - 1].nodeRef].nodeLat-Parser.m_minLat)/m_latInterval) * 100;
                    m_Y1 = ((_Network.nodes[_Network.ways[i].nodesInWay[j - 1].nodeRef].nodeLon-Parser.m_minLon)/m_lonInterval) * 100;
                    //prev node
                    m_X0 = ((_Network.nodes[_Network.ways[i].nodesInWay[j - 2].nodeRef].nodeLat-Parser.m_minLat)/m_latInterval) * 100;
                    m_Y0 = ((_Network.nodes[_Network.ways[i].nodesInWay[j - 2].nodeRef].nodeLon-Parser.m_minLon)/m_lonInterval) * 100;

                    float latDiff = m_X1-m_X0;
                    float lonDiff = m_Y1-m_Y0;
                    if(latDiff<0)
                    {
                        latDiff*=-1;
                    }
                    if(lonDiff<0)
                    {
                        lonDiff*=-1;
                    }
                    float sum =latDiff+lonDiff;

                    //original node
                    std::stringstream ss;
                    ss << "v " + (std::to_string(m_X1) + " 0.0 " + std::to_string(m_Y1) + "\n");
                    m_toOBJ = ss.str();
                    Writer.writeToOBJ(m_toOBJ);
                    m_toOBJ.clear();
                    m_verticeCount+=1;
                    m_verticeCountWay+=1;

                    //extra top node
                    std::stringstream sss;
                    m_Xtop0 = m_X1+(m_roadWidth*lonDiff/sum);
                    m_Ytop0 = m_Y1+(m_roadWidth*latDiff/sum);
                    sss << "v " + (std::to_string(m_Xtop0) + " 0.0 " + std::to_string(m_Ytop0) + "\n");
                    m_toOBJ = sss.str();
                    Writer.writeToOBJ(m_toOBJ);
                    m_toOBJ.clear();
                    m_verticeCount+=1;
                    m_verticeCountWay+=1;

                    //extra bottom node
                    std::stringstream ssss;
                    m_Xbot0 = m_X1-(m_roadWidth*lonDiff/sum);
                    m_Ybot0 = m_Y1-(m_roadWidth*latDiff/sum);
                    ssss << "v " + (std::to_string(m_Xbot0) + " 0.0 " + std::to_string(m_Ybot0) + "\n");
                    m_toOBJ = ssss.str();
                    Writer.writeToOBJ(m_toOBJ);
                    m_toOBJ.clear();
                    m_verticeCount+=1;
                    m_verticeCountWay+=1;
                }
            }
            //IMPLEMENTATION OF FACE ASSIGNING
            for(int k=(m_verticeCount-m_verticeCountWay)+1; k<m_verticeCount-3; k+=3)
            {
                faces << "f " + (std::to_string(k) + " " + std::to_string(k+3) + " " + std::to_string(k+4) + " " + std::to_string(k+1) + "\n");
            }
            for(int k=(m_verticeCount-m_verticeCountWay)+3; k<m_verticeCount-3; k+=3)
            {
                faces << "f " + (std::to_string(k) + " " + std::to_string(k+3) + " " + std::to_string(k+1) + " " + std::to_string(k-2) + "\n");
            }
        }
    }
    std::stringstream facePrep;
    facePrep << "s "+ std::to_string(1) + "\n";
    facePrep << "usemtl initialShadingGroup\n";
    m_toOBJ = facePrep.str();
    Writer.writeToOBJ(m_toOBJ);
    m_toOBJ.clear();

    m_toOBJ = faces.str();
    Writer.writeToOBJ(m_toOBJ);
    faces.clear();
    m_toOBJ.clear();
}

void GLWindow::useOriginalNetwork(bool)
{
    m_originalSystem=1;
}

void GLWindow::useNewNetwork(bool)
{
    m_originalSystem=0;
}

void GLWindow::outputToOBJ(bool)
{
    if(m_originalSystem==1)
    {
        OBJfill(Parser.Network);
    }
    else if(m_originalSystem==0)
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

    if(m_originalSystem==1)
    {
        drawNodes(Parser.Network);
    }
    else if(m_originalSystem==0)
    {
        drawNodes(Parser.NewNetwork);
    }

}

void GLWindow::timerEvent(QTimerEvent *)
{
    update();
}

//drawing all nodes and linking lines which represents the roads - ways
void GLWindow::drawNodes(network _Network)
{
    m_lonInterval = Parser.m_maxLon-Parser.m_minLon;
    m_latInterval = Parser.m_maxLat-Parser.m_minLat;

    glPointSize(3.0f);

    for( unsigned int i = 0; i<_Network.ways.size(); i++)
    {
        for(unsigned int j = 1; j<_Network.ways[i].nodesInWay.size(); j++)
        {
            m_X0 = ((_Network.nodes[_Network.ways[i].nodesInWay[j - 1].nodeRef].nodeLat-Parser.m_minLat)/m_latInterval) * 100;
            m_Y0 = ((_Network.nodes[_Network.ways[i].nodesInWay[j - 1].nodeRef].nodeLon-Parser.m_minLon)/m_lonInterval) * 100;
            m_X1 = ((_Network.nodes[_Network.ways[i].nodesInWay[j].nodeRef].nodeLat-Parser.m_minLat)/m_latInterval) * 100;
            m_Y1 = ((_Network.nodes[_Network.ways[i].nodesInWay[j].nodeRef].nodeLon-Parser.m_minLon)/m_lonInterval) * 100;

            glPushMatrix();
              glRotatef(90.0, 0.0, 0.0, 1.0);
              glTranslatef(-50.0f,-50.0f,0.0f);
              glBegin(GL_LINES);
              glColor3f(1.0,1.0,1.0);
              //drawing ways
              glVertex3f(m_X0, m_Y0, 0.0f);
              glVertex3f(m_X1, m_Y1, 0.0f);
              glEnd();
            glPopMatrix();
        }
    }
}

//first function when extending network, must first analyse existing data
void GLWindow::analyseNetwork(network Network)
{
    unsigned int totIntersections = 0;
    unsigned int maxIntersections = 0;
    unsigned int angleCount = 0;
    unsigned int distCount = 0;
    float totAngle = 0.0f;
    float distance=0.0f;
    m_maxAngle = 0.0f;
    m_minAngle = 2 * M_PI;
    m_minDistance = 1.0f;
    m_maxDistance = 0.0f;

    for(unsigned int i = 0; i < Network.ways.size(); i++)
    {
        if(Network.ways[i].intersections.size() > maxIntersections)
        {
            maxIntersections = Network.ways[i].intersections.size();
        }
        totIntersections += Network.ways[i].intersections.size();

        // calculating angle change between nodes
        for(unsigned int j = 1; j < Network.ways[i].nodesInWay.size() - 1; j++)
        {
            float magToPrev = sqrt((Network.ways[i].nodesInWay[j].nodeLat - Network.ways[i].nodesInWay[j-1].nodeLat)*(Network.ways[i].nodesInWay[j].nodeLat - Network.ways[i].nodesInWay[j-1].nodeLat) +
                                   (Network.ways[i].nodesInWay[j].nodeLon - Network.ways[i].nodesInWay[j-1].nodeLon)*(Network.ways[i].nodesInWay[j].nodeLon - Network.ways[i].nodesInWay[j-1].nodeLon));
            float magToNext = sqrt((Network.ways[i].nodesInWay[j].nodeLat - Network.ways[i].nodesInWay[j+1].nodeLat)*(Network.ways[i].nodesInWay[j].nodeLat - Network.ways[i].nodesInWay[j+1].nodeLat) +
                                   (Network.ways[i].nodesInWay[j].nodeLon - Network.ways[i].nodesInWay[j+1].nodeLon)*(Network.ways[i].nodesInWay[j].nodeLon - Network.ways[i].nodesInWay[j+1].nodeLon));
            float prevNormLat = (Network.ways[i].nodesInWay[j].nodeLat - Network.ways[i].nodesInWay[j-1].nodeLat);
            float prevNormLon = (Network.ways[i].nodesInWay[j].nodeLon - Network.ways[i].nodesInWay[j-1].nodeLon);
            float curNormLat = (Network.ways[i].nodesInWay[j].nodeLat - Network.ways[i].nodesInWay[j+1].nodeLat);
            float curNormLon = (Network.ways[i].nodesInWay[j].nodeLon - Network.ways[i].nodesInWay[j+1].nodeLon);
            float angle = acos((prevNormLat * curNormLat + prevNormLon * curNormLon)/(magToNext * magToPrev));

            //to stop unforseen errors
            if(std::isnan(angle)==false)
            {
                totAngle += angle;
                angleCount+=1;
            }
            //updating min and max angle if bigger or smaller is found
            if(angle > m_maxAngle)
            {
                m_maxAngle = angle;
            }
            if(angle < m_minAngle)
            {
                m_minAngle = angle;
            }
            if(magToPrev > m_maxDistance)
            {
                m_maxDistance = magToPrev;
            }
            if(magToPrev < m_minDistance)
            {
                m_minDistance = magToPrev;
            }
            distance+=magToPrev;
            distCount++;
        }
    }

    m_avgIntersections = totIntersections / Network.ways.size();
    m_avgNodes = Network.nodes.size() / Network.ways.size();
    m_avgDistance = distance/distCount;
    m_avgAngle = totAngle / angleCount;
}

//using values analyzed from original graph with random permutations
void GLWindow::extendNetwork()
{
    srand (time (NULL));
    unsigned int node_Ref = Parser.Network.nodes.size();
    unsigned int way_Ref;
    unsigned int numberOfNodes;
    //keep track of how many nodes and intersection points already used
    unsigned int nodesInWay;
    unsigned int interInWay;
    bool intersectPoint=false;

    //start checking for an unfinished node
    for( unsigned int i = 0; i<Parser.NewNetwork.ways.size(); i++)
    {
        for(unsigned int j = 1; j<Parser.NewNetwork.ways[i].nodesInWay.size(); j++)
        {
            //need to be editing the latest way added, so this should always update itself when a way is pushed back
            way_Ref=Parser.NewNetwork.ways.size();
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

                std::mt19937 rng(time(NULL));
                std::uniform_int_distribution<unsigned int> gen(3, 14);
                unsigned int randomNodes = gen(rng);
                std::uniform_int_distribution<unsigned int> gen2(2, 5);
                unsigned int randomIntersection = gen2(rng);

                numberOfNodes=m_avgNodes+randomNodes;
                unsigned int numberOfIntersections=m_avgIntersections+randomIntersection;

                //calculating length for each node, clamped to max and min of original network
                std::uniform_real_distribution<float> genLength(m_minDistance, m_maxDistance);
                float randomLengthWay = m_avgDistance + (genLength(rng)/2);
                if(randomLengthWay > m_maxDistance)
                {
                    randomLengthWay = m_maxDistance;
                }
                else if(randomLengthWay < m_minDistance)
                {
                    randomLengthWay = m_minDistance;
                }
                //calculating angle for each node, clamped to max and min of original network
                float randomAngleWay = m_avgAngle + (-m_avgAngle) + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/((m_maxAngle)-(-m_maxAngle))));
                if(randomAngleWay > m_maxAngle)
                {
                    randomAngleWay = m_maxAngle;
                }
                else if(randomAngleWay < m_minAngle)
                {
                    randomAngleWay = m_minAngle;
                }

                //push back nodes one at a time then for each node (loop through the number of nodes in this new way)
                for(unsigned int k=0; k<numberOfNodes; k++)
                {
                    node emptyNode;
                    Parser.NewNetwork.ways[way_Ref].nodesInWay.push_back(emptyNode);

                    //small random variation on overall way values - otherwise we just get straight lines
                    float randomLength = (randomLengthWay + (-randomLengthWay/10) + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/((randomLengthWay/10)-(-randomLengthWay/10)))))/20;
                    float randomAngle = randomAngleWay + (-randomAngleWay/10) + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/((randomAngleWay/10)-(-randomAngleWay/10))));

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
                        float lat=0.0f, lon=0.0f;

                        lat = Parser.NewNetwork.ways[way_Ref].nodesInWay[k-1].nodeLat + randomLength * cos(randomAngle);
                        lon = Parser.NewNetwork.ways[way_Ref].nodesInWay[k-1].nodeLon + randomLength * cos((M_PI/2) - randomAngle);

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
                            Parser.NewNetwork.ways[way_Ref].nodesInWay[k].isIntersection=true;
                            interInWay+=1;
                        }
                        else if(intersectPoint==false)
                        {
                            Parser.NewNetwork.ways[way_Ref].nodesInWay[k].isIntersection=false;
                            nodesInWay+=1;
                        }
                    }
                    //finally update node and way count
                    Parser.NewNetwork.ways[way_Ref].nodesInWay[k].nodeRef=node_Ref;
                    Parser.NewNetwork.nodes.push_back(Parser.NewNetwork.ways[way_Ref].nodesInWay[k]);
                }
            }
        }
    }
}

void GLWindow::createNewNetwork(bool)
{
    //first find info about current network
    analyseNetwork(Parser.Network);
    //step 2 - extend network
    extendNetwork();
    //update map on screen to new
    m_originalSystem=0;
}
