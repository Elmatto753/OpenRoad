#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  m_gl = new GLWindow(this);

  ui->m_scene->addWidget(m_gl, 0, 0, 1, 1);
//  connect(ui->m_Parse, SIGNAL(clicked(bool)), m_gl, SLOT(test(bool)));
  connect(ui->m_FileBrowse, SIGNAL(clicked(bool)), m_gl, SLOT(openFileBrowser(bool)));
  connect(ui->m_generateNetwork, SIGNAL(clicked(bool)), m_gl, SLOT(createNewNetwork(bool)));
  connect(ui->m_oldNetwork, SIGNAL(clicked(bool)), m_gl, SLOT(useOriginalNetwork(bool)));
  connect(ui->m_newNetwork, SIGNAL(clicked(bool)), m_gl, SLOT(useNewNetwork(bool)));
  connect(ui->m_output, SIGNAL(clicked(bool)), m_gl, SLOT(outputToOBJ(bool)));
  connect(this, SIGNAL(imasignal(int, std::string)), this, SLOT(receiverthingy(int, std::string)));

  emit imasignal(5, "signal test");
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *_event)
{
    switch(_event->key())
    {
        case Qt::Key_Escape : QGuiApplication::exit(0); break;
        case Qt::Key_W : glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
        case Qt::Key_S : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
    }
}
