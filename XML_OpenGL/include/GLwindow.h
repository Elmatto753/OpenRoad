#ifndef GLWINDOW_H__
#define GLWINDOW_H__

#include <QOpenGLWindow>
#include <QOpenGLWidget>
#include <QFileDialog>
#include <iostream>
#include "XMLParser.h"

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

    QString openFileBrowser(bool);

  private:
    float m_y;
    void timerEvent(QTimerEvent *);
    XMLParse Parser;
    QString fileName;
};

#endif
