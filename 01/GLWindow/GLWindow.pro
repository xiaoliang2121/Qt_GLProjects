QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


#CONFIG += c++11

TARGET = OpenGLWindow
#CONFIG -= app_bundle

TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

HEADERS += \
    glwindow.h

SOURCES += \
    glwindow.cpp \
    main.cpp

win32{
    LIBS += -lopengl32 -lglu32
}

unix{
    LIBS += -L/usr/local/lib -lGLU
}
