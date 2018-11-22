#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QOpenGLWindow>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>

class MainWindow : public QOpenGLWindow, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

    virtual void keyPressEvent(QKeyEvent *ev);

private:
    void initShaders();

    QOpenGLBuffer *vbo, *ibo;
    QOpenGLVertexArrayObject *vao;
    QOpenGLShaderProgram program;
};

#endif // MAINWINDOW_H
