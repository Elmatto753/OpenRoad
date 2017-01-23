#ifndef GLWINDOW_H_
#define GLWINDOW_H_

#include <QOpenGLWindow>
#include <QOpenGLWidget>
#include <QFileDialog>
#include <iostream>
#include "XMLParser.h"
#include "OBJWrite.h"

class GLWindow : public QOpenGLWidget
{
Q_OBJECT
public:
    GLWindow(QWidget *_parent);
    ~GLWindow();
    void initializeGL();
    void resizeGL(int _w, int _h);
    void paintGL();
    void drawNodes(network _Network);
    void OBJfill(network _Network);

//Linked to UI form
public slots:
    void outputToOBJ(bool);
    void createNewNetwork(bool);
    void useOriginalNetwork(bool);
    void useNewNetwork(bool);
    QString openFileBrowser(bool);

private:
    XMLParse Parser;
    OBJWrite Writer;
    QString fileName;

    //functions
    void timerEvent(QTimerEvent *);
    void analyseNetwork(network Network);
    void fillNetwork();
    void extendNetwork();

    //variables
    std::string m_toOBJ;
    uint m_avgIntersections;
    uint m_avgNodes;
    int m_verticeCount;
    int m_verticeCountWay;
    //allowing users a choice of which road system to use
    int m_originalSystem;
    float m_y;
    //for network drawing and vertice creation
    float m_lonInterval = Parser.m_maxLon-Parser.m_minLon;
    float m_latInterval = Parser.m_maxLat-Parser.m_minLat;
    float m_X0, m_X1, m_Y0, m_Y1, m_Xtop0, m_Ytop0, m_Xbot0, m_Ybot0;
    float m_roadWidth;
    //analysis of road network
    float m_avgDistance;
    float m_minDistance;
    float m_maxDistance;
    float m_avgAngle;
    float m_maxAngle;
    float m_minAngle;
};

#endif //_GLWINDOW_H_
