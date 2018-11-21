#include "glwindow.h"
#include <GL/glu.h>
#include <QKeyEvent>

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

GLWindow::~GLWindow()
{

}

void GLWindow::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0f,0.0f,0.0f,1.0f);
}

void GLWindow::resizeGL(int width, int height)
{
    GLfloat fAspect;

    if(height == 0)
        height = 1;

    fAspect = (GLfloat)width/(GLfloat)height;

    glViewport(0,0,width,height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(35.0,fAspect,1.0,65.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GLWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
        glTranslatef(0.0f,0.0f,-3.0f);
        glRotatef(xRot,1.0f,0.0f,0.0f);
        glRotatef(yRot,0.0f,1.0f,0.0f);

        glBegin(GL_TRIANGLES);
            glColor3f(1.0f,0.0f,0.0f);
            glVertex3f(0.0f,0.75f,0.0f);

            glColor3f(0.0f,1.0f,0.0f);
            glVertex3f(-0.5f,0.0f,0.0f);

            glColor3f(0.0f,0.0f,1.0f);
            glVertex3f(0.5f,0.0f,0.0f);
        glEnd();
        glPopMatrix();
}

void GLWindow::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key() == Qt::Key_Up)
        xRot -= 5.0f;

    if(ev->key() == Qt::Key_Down)
        xRot += 5.0f;

    if(ev->key() == Qt::Key_Left)
        yRot -= 5.0f;

    if(ev->key() == Qt::Key_Right)
        yRot += 5.0f;

    if(xRot > 360.0f)
        xRot = 5.0f;

    if(yRot > 360.0f)
        yRot = 5.0f;

    if(xRot < 0.0f)
        xRot = 355.0f;

    if(yRot < 0.0f)
        yRot = 355.0f;

    update();
}
