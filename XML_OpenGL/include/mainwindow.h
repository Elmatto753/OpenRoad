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

public slots:
  void receiverthingy(int _s, std::string _ss) { std::cout << _s << ": " << _ss << "\n"; }

signals:
  void imasignal(int, std::string);
};

#endif // MAINWINDOW_H
