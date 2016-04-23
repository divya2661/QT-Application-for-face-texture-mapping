#-------------------------------------------------
#
# Project created by QtCreator 2016-04-15T06:18:24
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG+=qml_debug

TARGET = openGL
TEMPLATE = app
INCLUDEPATH += /home/divya/Qt/boost/

SOURCES += main.cpp\
        window.cpp \
    glwidget.cpp \
    function.cpp \
    dialog.cpp \
    glwidget1.cpp \
    mdialog.cpp \
    errordialog.cpp

HEADERS  += window.h \
    glwidget.h \
    point.h \
    index.h \
    function.h \
    grammer.hpp \
    dialog.h \
    glwidget1.h \
    mdialog.h \
    errordialog.h

FORMS    += window.ui \
    dialog.ui \
    mdialog.ui \
    errordialog.ui

LIBS += -lglut -lGLU

RESOURCES += \
    resources.qrc

