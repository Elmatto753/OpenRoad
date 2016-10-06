#include "GLwindow.h"
#include <GL/glu.h>
#include <QKeyEvent>
#include <QGuiApplication>

GLWindow::GLWindow()
{
    setTitle("Simple GL Window");
    m_y=0.0f;
}

GLWindow::~GLWindow()
{

}

void GLWindow::initializeGL()
{
    glClearColor(0.6,  0.6, 0.6, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45,float(width()/height()),0.1,20);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(2,2,2,0,0,0,0,1,0);
    startTimer(1);
}

void GLWindow::resizeGL(int _w, int _h)
{
    glViewport(0,0,_w,_h);
}

void GLWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glRotatef(m_y, 0.0, 1.0, 0.0);
    glBegin(GL_TRIANGLES);
        glColor3f(1.0,0.0,0.0);
        glVertex3f(0.0,1.0,0.0);

        glColor3f(0.0,1.0,0.0);
        glVertex3f(-1.0,0.0,0.0);

        glColor3f(0.0,0.0,1.0);
        glVertex3f(1.0,0.0,0.0);
    glEnd();
    glPopMatrix();
}

void GLWindow::timerEvent(QTimerEvent *)
{
    m_y+=0.1;
    update();
}

void GLWindow::keyPressEvent(QKeyEvent *_event)
{
    switch(_event->key())
    {
        case Qt::Key_Escape : QGuiApplication::exit(0); break;
        case Qt::Key_W : glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
        case Qt::Key_S : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
    }
}
