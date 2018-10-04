QT += core gui widgets

TARGET = glWidget
TEMPLATE = app
CONFIG += c++11

HEADERS += \
    myglwidget.h \
    dialog.h

SOURCES += \
    myglwidget.cpp \
    main.cpp \
    dialog.cpp

FORMS += \
    dialog.ui
