#ifndef GLWINDOW_H__
#define GLWINDOW_H__

#include <QOpenGLWindow>

class GLWindow : public QOpenGLWindow
{
  public:
    GLWindow();
    ~GLWindow();
    void initializeGL();
    void resizeGL(int _w, int _h);
    void paintGL();

  private:
    float m_y;
    void timerEvent(QTimerEvent *);
    void keyPressEvent(QKeyEvent *_event);
};

#endif
