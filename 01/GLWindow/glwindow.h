#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <QOpenGLWindow>
#include <QOpenGLFunctions>

class GLWindow : public QOpenGLWindow, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    ~GLWindow();

public:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

protected:
    virtual void keyPressEvent(QKeyEvent *ev);
};

#endif // GLWINDOW_H
