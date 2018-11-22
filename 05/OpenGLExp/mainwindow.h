#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QOpenGLWindow>
#include <QSurfaceFormat>
#include <QOpenGLFunctions>

#include <QtOpenGL/QtOpenGL>
#include <gl/GLU.h>

class MainWindow : public QOpenGLWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);

public slots:
    void UpdateAnimation();

private:
    QOpenGLContext *context;
    QOpenGLFunctions *funs;

    GLfloat rotation;
};

#endif // MAINWINDOW_H
