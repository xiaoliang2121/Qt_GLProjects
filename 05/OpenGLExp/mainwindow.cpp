#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
    rotation(0)
{
    setSurfaceType(QWindow::OpenGLSurface);

    QSurfaceFormat format;
    format.setProfile(QSurfaceFormat::CompatibilityProfile);
    format.setVersion(2,1);
    setFormat(format);

    context = new QOpenGLContext;
    context->setFormat(format);
    context->create();
    context->makeCurrent(this);

    funs = context->functions();

    QTimer *timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&MainWindow::UpdateAnimation);
    timer->start(60);
}

MainWindow::~MainWindow()
{

}

void MainWindow::initializeGL()
{
    glEnable(GL_DEPTH_TEST);

    resizeGL(width(),height());
}

void MainWindow::resizeGL(int w, int h)
{
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
    // set viewport
    glViewport(0,0,w,h);

    qreal aspectratio = qreal(w)/qreal(h);
    //glOrtho(-1*aspectratio,1*aspectratio,-1,1,1,-1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(75,aspectratio,0.1,400000000);

    // Initialize Model View Matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void MainWindow::paintGL()
{
    //glClearColor(1.0f,0.0f,0.0f,0.0f);
//    glClear(GL_COLOR_BUFFER_BIT);

//        glBegin(GL_QUADS);

//        glColor3f(1.0f,0.0f,0.0f);
//        glVertex2f(-0.5f,-0.5f);

//        glColor3f(0.0f,1.0f,0.0f);
//        glVertex2f(0.5f,-0.5f);

//        glColor3f(0.0f,0.0f,1.0f);
//        glVertex2f(0.5f,0.5f);

//        glColor3f(0.0f,0.5f,0.5f);
//        glVertex2f(-0.5f,0.5f);
//        glEnd();

//        glBegin(GL_TRIANGLES);

//        glColor3f(1.0f,0.0f,0.0f);
//        glVertex2f(-0.4f,-0.4f);
//        glColor3f(0.0f,1.0f,0.0f);
//        glVertex2f(0.8f,-0.1f);
//        glColor3f(0.0f,0.0f,1.0f);
//        glVertex2f(-0.1f,-0.8f);

//        glEnd();

    glClearColor(0.39f, 0.58f, 0.93f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glTranslatef(0.0, 0.0, -3.0);
        glRotatef(rotation, 1.0, 1.0, 1.0);


        // FRONT
        glBegin(GL_POLYGON);
            glColor3f(0.0,  0.0, 0.0);
            glVertex3f(0.5, -0.5, -0.5);
            glVertex3f(0.5, 0.5, -0.5);
            glVertex3f(-0.5, 0.5, -0.5);
            glVertex3f(-0.5, -0.5, -0.5);
        glEnd();

        // BACK
        glBegin(GL_POLYGON);
            glColor3f(0.0,  1.0, 0.0);
            glVertex3f(0.5, -0.5, 0.5);
            glVertex3f(0.5, 0.5, 0.5);
            glVertex3f(-0.5, 0.5, 0.5);
            glVertex3f(-0.5, -0.5, 0.5);
        glEnd();

        // RIGHT
        glBegin(GL_POLYGON);
            glColor3f(1.0, 0.0, 1.0);
            glVertex3f(0.5, -0.5, -0.5);
            glVertex3f(0.5, 0.5, -0.5);
            glVertex3f(0.5, 0.5, 0.5);
            glVertex3f(0.5, -0.5, 0.5);
        glEnd();

        // LEFT
        glBegin(GL_POLYGON);
            glColor3f(1.0, 1.0, 0.0);
            glVertex3f(-0.5, -0.5, 0.5);
            glVertex3f(-0.5, 0.5, 0.5);
            glVertex3f(-0.5, 0.5, -0.5);
            glVertex3f(-0.5, -0.5, -0.5);
        glEnd();

        // TOP
        glBegin(GL_POLYGON);
            glColor3f(0.0, 0.0, 1.0);
            glVertex3f(0.5, 0.5, 0.5);
            glVertex3f(0.5, 0.5, -0.5);
            glVertex3f(-0.5, 0.5, -0.5);
            glVertex3f(-0.5, 0.5, 0.5);
        glEnd();

        // Red side - BOTTOM
        glBegin(GL_POLYGON);
            glColor3f(1.0, 0.0, 0.0);
            glVertex3f(0.5, -0.5, -0.5);
            glVertex3f(0.5, -0.5, 0.5);
            glVertex3f(-0.5, -0.5, 0.5);
            glVertex3f(-0.5, -0.5, -0.5);
        glEnd();

        glFlush();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    resizeGL(width(),height());
    update();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    paintGL();
}

void MainWindow::UpdateAnimation()
{
    rotation += 10;
    update();
}
