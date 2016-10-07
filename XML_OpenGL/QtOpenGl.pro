TARGET=Roads
CONFIG+=c++11
CONFIG-= x86_64 app_bundle

OBJECTS_DIR=obj
MOC_DIR=moc
QT+= opengl core gui

INCLUDEPATH+=./include \
            /usr/local/include

SOURCES+=$$PWD/src/main.cpp \
         $$PWD/src/GLwindow.cpp \
         $$PWD/src/XMLParser.cpp

HEADERS+=$$PWD/include/GLwindow.h \
         $$PWD/include/XMLParser.h

DESTDIR=./

macx:LIBS+= -framework OpenGL

linux: LIBS+= -lGLU

OTHER_FILES += data/map.osm \
               data/map_1.osm
