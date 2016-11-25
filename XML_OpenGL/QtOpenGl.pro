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
         $$PWD/src/XMLParser.cpp \
         $$PWD/src/mainwindow.cpp \
         $$PWD/src/OBJWrite.cpp

HEADERS+=$$PWD/include/GLwindow.h \
         $$PWD/include/XMLParser.h \
         $$PWD/include/mainwindow.h \
         $$PWD/include/OBJWrite.h

FORMS    += $$PWD/UI/mainwindow.ui
UI_DIR = $$PWD/include
UI_HEADERS_DIR = $$PWD/include

DESTDIR=./

macx:LIBS+= -framework OpenGL

linux: LIBS+= -lGLU

OTHER_FILES += data/map.osm \
               data/map_1.osm \
               data/bigmap.osm \
               data/biggermap.osm \
               data/NYmap.osm \
               data/SoL.osm \
               data/venice \
               data/EastEnders.osm \
               data/EastEnders_2.osm \
               data/crazy_0 \
               data/NY \
               data/sydney_0 \
               data/HK \
               data/cardiff \
               data/Philland \
               data/test.osm
