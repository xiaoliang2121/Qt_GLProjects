QT += core gui

CONFIG += c++11

TARGET = OpenGLWindow
CONFIG -= app_bundle

TEMPLATE = app

HEADERS += \
    glwindow.h

SOURCES += \
    glwindow.cpp \
    main.cpp

LIBS += -L/usr/local/lib -lGLU
