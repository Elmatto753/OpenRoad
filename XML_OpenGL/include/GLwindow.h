#ifndef GLWINDOW_H__
#define GLWINDOW_H__

#include <QOpenGLWindow>
#include <QOpenGLWidget>
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
    void test(bool _s);
    void slider(int);

  private:
    float m_y;
    void timerEvent(QTimerEvent *);
    void keyPressEvent(QKeyEvent *_event);
    XMLParse Parser;
};

#endif
