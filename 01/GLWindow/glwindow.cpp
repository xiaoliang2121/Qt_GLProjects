#include "glwindow.h"

GLWindow::~GLWindow()
{

}

void GLWindow::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.3f,0.8f,0.0f,1.0f);
}

void GLWindow::resizeGL(int width, int height)
{
    glViewport(0,0,width,height);
}

void GLWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
}
