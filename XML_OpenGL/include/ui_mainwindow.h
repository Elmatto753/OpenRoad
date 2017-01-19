/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
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
    QFrame *line_6;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *verticalSpacer_12;
    QSpacerItem *verticalSpacer_7;
    QTextBrowser *textBrowser;
    QSpacerItem *verticalSpacer_6;
    QSpacerItem *verticalSpacer_10;
    QFrame *line_7;
    QTextBrowser *textBrowser_4;
    QSpacerItem *verticalSpacer_4;
    QFrame *line_2;
    QFrame *line_4;
    QTextBrowser *textBrowser_2;
    QPushButton *m_generateNetwork;
    QFrame *line;
    QSpacerItem *verticalSpacer_3;
    QFrame *line_8;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer_11;
    QSpacerItem *verticalSpacer_9;
    QFrame *line_5;
    QTextBrowser *textBrowser_3;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QPushButton *m_oldNetwork;
    QPushButton *m_newNetwork;
    QPushButton *m_FileBrowse;
    QFrame *line_3;
    QPushButton *m_output;
    QSpacerItem *verticalSpacer_8;
    QSpacerItem *verticalSpacer_13;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1190, 756);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        SceneLayout = new QWidget(centralWidget);
        SceneLayout->setObjectName(QStringLiteral("SceneLayout"));
        SceneLayout->setGeometry(QRect(0, -1, 991, 721));
        m_scene = new QGridLayout(SceneLayout);
        m_scene->setSpacing(6);
        m_scene->setContentsMargins(11, 11, 11, 11);
        m_scene->setObjectName(QStringLiteral("m_scene"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        m_scene->addItem(horizontalSpacer, 0, 0, 1, 1);

        ButtonLayout = new QWidget(centralWidget);
        ButtonLayout->setObjectName(QStringLiteral("ButtonLayout"));
        ButtonLayout->setGeometry(QRect(980, 0, 211, 720));
        m_buttons = new QGridLayout(ButtonLayout);
        m_buttons->setSpacing(6);
        m_buttons->setContentsMargins(11, 11, 11, 11);
        m_buttons->setObjectName(QStringLiteral("m_buttons"));
        line_6 = new QFrame(ButtonLayout);
        line_6->setObjectName(QStringLiteral("line_6"));
        line_6->setFrameShape(QFrame::HLine);
        line_6->setFrameShadow(QFrame::Sunken);

        m_buttons->addWidget(line_6, 22, 0, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 35, QSizePolicy::Minimum, QSizePolicy::Expanding);

        m_buttons->addItem(verticalSpacer_5, 21, 0, 1, 1);

        verticalSpacer_12 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Expanding);

        m_buttons->addItem(verticalSpacer_12, 23, 0, 1, 1);

        verticalSpacer_7 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Expanding);

        m_buttons->addItem(verticalSpacer_7, 5, 0, 1, 1);

        textBrowser = new QTextBrowser(ButtonLayout);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(textBrowser->sizePolicy().hasHeightForWidth());
        textBrowser->setSizePolicy(sizePolicy);
        textBrowser->setMaximumSize(QSize(16777215, 65));

        m_buttons->addWidget(textBrowser, 3, 0, 1, 1);

        verticalSpacer_6 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Expanding);

        m_buttons->addItem(verticalSpacer_6, 2, 0, 1, 1);

        verticalSpacer_10 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Expanding);

        m_buttons->addItem(verticalSpacer_10, 16, 0, 1, 1);

        line_7 = new QFrame(ButtonLayout);
        line_7->setObjectName(QStringLiteral("line_7"));
        line_7->setFrameShape(QFrame::HLine);
        line_7->setFrameShadow(QFrame::Sunken);

        m_buttons->addWidget(line_7, 15, 0, 1, 1);

        textBrowser_4 = new QTextBrowser(ButtonLayout);
        textBrowser_4->setObjectName(QStringLiteral("textBrowser_4"));
        sizePolicy.setHeightForWidth(textBrowser_4->sizePolicy().hasHeightForWidth());
        textBrowser_4->setSizePolicy(sizePolicy);
        textBrowser_4->setMaximumSize(QSize(16777215, 50));

        m_buttons->addWidget(textBrowser_4, 24, 0, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 35, QSizePolicy::Minimum, QSizePolicy::Expanding);

        m_buttons->addItem(verticalSpacer_4, 14, 0, 1, 1);

        line_2 = new QFrame(ButtonLayout);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        m_buttons->addWidget(line_2, 6, 0, 1, 1);

        line_4 = new QFrame(ButtonLayout);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        m_buttons->addWidget(line_4, 20, 0, 1, 1);

        textBrowser_2 = new QTextBrowser(ButtonLayout);
        textBrowser_2->setObjectName(QStringLiteral("textBrowser_2"));
        sizePolicy.setHeightForWidth(textBrowser_2->sizePolicy().hasHeightForWidth());
        textBrowser_2->setSizePolicy(sizePolicy);
        textBrowser_2->setMaximumSize(QSize(16777215, 60));

        m_buttons->addWidget(textBrowser_2, 10, 0, 1, 1);

        m_generateNetwork = new QPushButton(ButtonLayout);
        m_generateNetwork->setObjectName(QStringLiteral("m_generateNetwork"));

        m_buttons->addWidget(m_generateNetwork, 11, 0, 1, 1);

        line = new QFrame(ButtonLayout);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        m_buttons->addWidget(line, 1, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 35, QSizePolicy::Minimum, QSizePolicy::Expanding);

        m_buttons->addItem(verticalSpacer_3, 7, 0, 1, 1);

        line_8 = new QFrame(ButtonLayout);
        line_8->setObjectName(QStringLiteral("line_8"));
        line_8->setFrameShape(QFrame::HLine);
        line_8->setFrameShadow(QFrame::Sunken);

        m_buttons->addWidget(line_8, 8, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 80, QSizePolicy::Minimum, QSizePolicy::Expanding);

        m_buttons->addItem(verticalSpacer_2, 0, 0, 1, 1);

        verticalSpacer_11 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Expanding);

        m_buttons->addItem(verticalSpacer_11, 19, 0, 1, 1);

        verticalSpacer_9 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Expanding);

        m_buttons->addItem(verticalSpacer_9, 12, 0, 1, 1);

        line_5 = new QFrame(ButtonLayout);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);

        m_buttons->addWidget(line_5, 27, 0, 1, 1);

        textBrowser_3 = new QTextBrowser(ButtonLayout);
        textBrowser_3->setObjectName(QStringLiteral("textBrowser_3"));
        sizePolicy.setHeightForWidth(textBrowser_3->sizePolicy().hasHeightForWidth());
        textBrowser_3->setSizePolicy(sizePolicy);
        textBrowser_3->setMaximumSize(QSize(16777215, 90));

        m_buttons->addWidget(textBrowser_3, 17, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 80, QSizePolicy::Minimum, QSizePolicy::Expanding);

        m_buttons->addItem(verticalSpacer, 28, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        m_oldNetwork = new QPushButton(ButtonLayout);
        m_oldNetwork->setObjectName(QStringLiteral("m_oldNetwork"));

        horizontalLayout->addWidget(m_oldNetwork);

        m_newNetwork = new QPushButton(ButtonLayout);
        m_newNetwork->setObjectName(QStringLiteral("m_newNetwork"));

        horizontalLayout->addWidget(m_newNetwork);


        m_buttons->addLayout(horizontalLayout, 18, 0, 1, 1);

        m_FileBrowse = new QPushButton(ButtonLayout);
        m_FileBrowse->setObjectName(QStringLiteral("m_FileBrowse"));

        m_buttons->addWidget(m_FileBrowse, 4, 0, 1, 1);

        line_3 = new QFrame(ButtonLayout);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        m_buttons->addWidget(line_3, 13, 0, 1, 1);

        m_output = new QPushButton(ButtonLayout);
        m_output->setObjectName(QStringLiteral("m_output"));

        m_buttons->addWidget(m_output, 25, 0, 1, 1);

        verticalSpacer_8 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Expanding);

        m_buttons->addItem(verticalSpacer_8, 9, 0, 1, 1);

        verticalSpacer_13 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Expanding);

        m_buttons->addItem(verticalSpacer_13, 26, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1190, 22));
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
        textBrowser->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'.SF NS Text'; font-size:13pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt;\">Step 1: Please click on the button to load your chosen file which has been downloaded from OpenStreetMaps (OSM)</span></p></body></html>", 0));
        textBrowser_4->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'.SF NS Text'; font-size:13pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt;\">Step 3: Click below to populate output file with geometry for the road network</span></p></body></html>", 0));
        textBrowser_2->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'.SF NS Text'; font-size:13pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt;\">Step 2: Click below to procedurally generate a new road network based off of the input example data</span></p></body></html>", 0));
        m_generateNetwork->setText(QApplication::translate("MainWindow", "Generate Network", 0));
        textBrowser_3->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'.SF NS Text'; font-size:13pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt;\">These buttons can be used to select which road network you wish to use, the original data from OSM or the new network</span></p></body></html>", 0));
        m_oldNetwork->setText(QApplication::translate("MainWindow", "Original", 0));
        m_newNetwork->setText(QApplication::translate("MainWindow", "New", 0));
        m_FileBrowse->setText(QApplication::translate("MainWindow", "Open File", 0));
        m_output->setText(QApplication::translate("MainWindow", "Output to OBJ", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
