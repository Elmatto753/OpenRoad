#ifndef GLWINDOW_H__
#define GLWINDOW_H__

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

  public slots:
    void test(bool);
    void slider(int);
    void outputToOBJ(bool);
    void createNewNetwork(bool);
    void useOriginalNetwork(bool);
    void useNewNetwork(bool);
    QString openFileBrowser(bool);

signals:
  //void imasignal();

  private:
    float m_y;
    void timerEvent(QTimerEvent *);
    void analyseNetwork(network Network);
    void fillNetwork();
    void extendNetwork();

    XMLParse Parser;
    OBJWrite Writer;
    QString fileName;
    bool OBJwritten = false;
    float lonInterval = Parser.maxLon-Parser.minLon;
    float latInterval = Parser.maxLat-Parser.minLat;
    float X0, X1, Y0, Y1, Xtop0, Ytop0, Xbot0, Ybot0;
    std::string toOBJ;
    float roadWidth;
    int verticeCount;

    uint avgIntersections;
    uint avgNodes;
    float avgDistance;
    float minDistance;
    float maxDistance;
    float avgAngle;
    float maxAngle;
    float minAngle;

    //allowing users a choice of which road system to use
    int originalSystem;
};

#endif
