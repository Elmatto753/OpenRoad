TARGET=Roads
CONFIG+=c++11
CONFIG-= x86_64 app_bundle

OBJECTS_DIR=obj
MOC_DIR=moc
QT+= opengl core gui

INCLUDEPATH+=./include \
            /usr/local/include
win32{
INCLUDEPATH+= "D:\InstalledPrograms\boost_1_64_0"
LIBS += -lOpengl32 -lGLU32
}


SOURCES+=$$PWD/src/main.cpp \
         $$PWD/src/GLWindow.cpp \
         $$PWD/src/XMLParser.cpp \
         $$PWD/src/MainWindow.cpp \
         $$PWD/src/OBJWrite.cpp

HEADERS+=$$PWD/include/GLWindow.h \
         $$PWD/include/XMLParser.h \
         $$PWD/include/MainWindow.h \
         $$PWD/include/OBJWrite.h

FORMS    += $$PWD/UI/mainwindow.ui
UI_DIR = $$PWD/include
UI_HEADERS_DIR = $$PWD/include

DESTDIR=./

macx:LIBS+= -framework OpenGL

linux: LIBS+= -lGLU

OTHER_FILES += data/map.osm \
               data/bigmap.osm \
               data/EastEnders.osm \
               data/NY \
               data/HK \
               data/cardiff.osm \
               data/Philland \
               data/singleRoad_2.osm
