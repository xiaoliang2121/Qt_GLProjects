#include "glwindow.h"
#include "vertex.h"
#include <QOpenGLShaderProgram>

static const Vertex sg_vertexes[] = {
  Vertex(QVector3D( 0.00f,  0.75f, 1.0f), QVector3D(1.0f, 0.0f, 0.0f)),
  Vertex(QVector3D( 0.75f, -0.75f, 1.0f), QVector3D(0.0f, 1.0f, 0.0f)),
  Vertex(QVector3D(-0.75f, -0.75f, 1.0f), QVector3D(0.0f, 0.0f, 1.0f))
};

GLWindow::GLWindow()
{
}

GLWindow::~GLWindow()
{
    makeCurrent();
    m_object.destroy();
    m_vertex.destroy();
    delete m_program;
    doneCurrent();
}

void GLWindow::initializeGL()
{
    initializeOpenGLFunctions();
    printContextInfo();

    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);

    m_program = new QOpenGLShaderProgram();
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/triangle.vert");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/triangle.frag");
    m_program->link();
    m_program->bind();

    m_vertex.create();
    m_vertex.bind();
    m_vertex.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vertex.allocate(sg_vertexes, sizeof(sg_vertexes));

    m_object.create();
    m_object.bind();
    m_program->enableAttributeArray(0);
    m_program->enableAttributeArray(1);
    m_program->setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(), Vertex::PositionTupleSize, Vertex::stride());
    m_program->setAttributeBuffer(1, GL_FLOAT, Vertex::colorOffset(), Vertex::ColorTupleSize, Vertex::stride());
    qDebug()<<"offset "<<Vertex::positionOffset()<<" "
           <<"size "<<Vertex::PositionTupleSize<<" "
          <<"stride "<<Vertex::stride()<<endl;

    qDebug()<<"offset "<<Vertex::colorOffset()<<" "
           <<"size "<<Vertex::ColorTupleSize<<" "
          <<"stride "<<Vertex::stride()<<endl;

    m_object.release();
    m_vertex.release();
    m_program->release();
}

void GLWindow::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}

void GLWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    m_program->bind();
    m_object.bind();
    glDrawArrays(GL_TRIANGLES, 0, sizeof(sg_vertexes) / sizeof(sg_vertexes[0]));
    m_object.release();
    m_program->release();
}

void GLWindow::printContextInfo()
{
    QString glType;
    QString glVersion;

    glType = (context()->isOpenGLES()) ? "OpenGL ES" : "OpenGL";
    glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));

    qDebug()<<glType<<endl<<glVersion<<endl;
}
