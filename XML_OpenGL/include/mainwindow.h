#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <GLwindow.h>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
  Ui::MainWindow *ui;
  GLWindow *m_gl;
  QString *m_fileName;
  void keyPressEvent(QKeyEvent *_event);
  int test=0;


public slots:
  void receiverthingy() { test=1; }
};

#endif // MAINWINDOW_H
