TARGET=XMLParse
TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QT+=gui opengl core

# as I want to support 4.8 and 5 this will set a flag for some of the mac stuff
# mainly in the types.h file for the setMacVisual which is native in Qt5
isEqual(QT_MAJOR_VERSION, 5) {
        cache()
        DEFINES +=QT5BUILD
}
# where to put moc auto generated files
MOC_DIR=moc
# on a mac we don't create a .app bundle file ( for ease of multiplatform use)
CONFIG-=app_bundle

# and add the include dir into the search path for Qt and make
INCLUDEPATH +=./include \
              /usr/local/include
# where our exe is going to live (root of project)
DESTDIR=./

SOURCES += main.cpp

OTHER_FILES += data/map.osm

LIBS+= -framework OpenGL

# LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -L/usr/local/lib -I/opt/X11/lib

LINKER_FLAGS = -framework OpenGL -lglfw3 -lglew


