#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QMainWindow>
#include <GLWindow.h>

namespace Ui
{
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
};

#endif // _MAINWINDOW_H_
