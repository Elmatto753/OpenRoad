#ifndef GLWINDOW_H__
#define GLWINDOW_H__

#include <QOpenGLWindow>
#include <QOpenGLWidget>
#include <QFileDialog>
#include <iostream>
#include "XMLParser.h"
#include "OBJWrite.h"

class GLWindow : public QOpenGLWidget//public QOpenGLWindow
{
  Q_OBJECT
  public:
    GLWindow(QWidget *_parent);
    ~GLWindow();
    void initializeGL();
    void resizeGL(int _w, int _h);
    void paintGL();
    void drawNodes();

  public slots:
    void test(bool);
    void slider(int);
    void outputToOBJ(bool);
    QString openFileBrowser(bool);

  private:
    float m_y;
    void timerEvent(QTimerEvent *);
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
};

#endif
