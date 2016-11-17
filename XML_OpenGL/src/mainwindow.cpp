#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  m_gl = new GLWindow(this);

  ui->m_scene->addWidget(m_gl, 0, 0, 1, 1);
  connect(ui->m_clickme, SIGNAL(clicked(bool)), m_gl, SLOT(test(bool)));
  connect(ui->m_slider, SIGNAL(sliderMoved(int)), m_gl, SLOT(slider(int)));
  connect(this, SIGNAL(imasignal(int, std::string)), this, SLOT(receiverthingy(int, std::string)));

  emit imasignal(5, "Phil is a dumdum");
}

MainWindow::~MainWindow()
{
  delete ui;
}
