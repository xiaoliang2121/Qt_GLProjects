#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QOpenGLWidget>

class MyGLWidget : public QOpenGLWidget
{
public:
    MyGLWidget(QWidget *parent = 0);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
};

#endif // MYGLWIDGET_H
