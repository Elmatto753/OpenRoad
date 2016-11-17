/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *SceneLayout;
    QGridLayout *m_scene;
    QSpacerItem *horizontalSpacer;
    QWidget *ButtonLayout;
    QGridLayout *m_buttons;
    QPushButton *m_clickme;
    QSpacerItem *verticalSpacer;
    QSlider *m_slider;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1020, 756);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        SceneLayout = new QWidget(centralWidget);
        SceneLayout->setObjectName(QStringLiteral("SceneLayout"));
        SceneLayout->setGeometry(QRect(0, 0, 720, 720));
        m_scene = new QGridLayout(SceneLayout);
        m_scene->setSpacing(6);
        m_scene->setContentsMargins(11, 11, 11, 11);
        m_scene->setObjectName(QStringLiteral("m_scene"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        m_scene->addItem(horizontalSpacer, 0, 0, 1, 1);

        ButtonLayout = new QWidget(centralWidget);
        ButtonLayout->setObjectName(QStringLiteral("ButtonLayout"));
        ButtonLayout->setGeometry(QRect(720, 0, 300, 720));
        m_buttons = new QGridLayout(ButtonLayout);
        m_buttons->setSpacing(6);
        m_buttons->setContentsMargins(11, 11, 11, 11);
        m_buttons->setObjectName(QStringLiteral("m_buttons"));
        m_clickme = new QPushButton(ButtonLayout);
        m_clickme->setObjectName(QStringLiteral("m_clickme"));

        m_buttons->addWidget(m_clickme, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        m_buttons->addItem(verticalSpacer, 2, 0, 1, 1);

        m_slider = new QSlider(ButtonLayout);
        m_slider->setObjectName(QStringLiteral("m_slider"));
        m_slider->setOrientation(Qt::Horizontal);

        m_buttons->addWidget(m_slider, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1020, 19));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        m_clickme->setText(QApplication::translate("MainWindow", "Clicka me", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
