#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <QOpenGLWindow>
//#include <QOpenGLExtraFunctions>
//#include <QOpenGLFunctions>
#include <QOpenGLFunctions_3_3_Core>
//#include <QtGui>

class GLWindow : public QOpenGLWindow, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT

public:
    ~GLWindow();

public:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
};

#endif // GLWINDOW_H
