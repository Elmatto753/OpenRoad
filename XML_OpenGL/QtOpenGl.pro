TARGET=Roads
CONFIG+=c++11
CONFIG   -= x86_64

OBJECTS_DIR=obj
MOC_DIR=moc
QT+= opengl core gui

INCLUDEPATH+=./include \
            /usr/local/include

SOURCES+=$$PWD/src/main.cpp \
         $$PWD/src/GLwindow.cpp

HEADERS+=$$PWD/include/GLwindow.h

macx:LIBS+= -framework OpenGL

LIBS+= -lGLU

OTHER_FILES += data/map.osm
