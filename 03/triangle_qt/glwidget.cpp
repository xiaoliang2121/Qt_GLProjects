#include "glwidget.h"
#include <QVector3D>
#include <QOpenGLShaderProgram>

struct VertexData
{
    QVector3D position;
    QVector3D color;
};

GLWidget::GLWidget():
    IBO(QOpenGLBuffer::IndexBuffer),        // 这里要设置成索引buffer
    shaderProgram(nullptr)
{
}

GLWidget::~GLWidget()
{
    makeCurrent();
    VAO.destroy();
    VBO.destroy();
    IBO.destroy();
    delete shaderProgram;
    doneCurrent();
}

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    printContextInfo();

    glClearColor(0.7f,0.7f,0.7f,1.0f);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    initShaders();

    VertexData vertices[] = {
        {QVector3D(-0.5f,-0.5f,0.0f),QVector3D(1.0f,0.0f,0.0f)},    // 左下
        {QVector3D(0.5f,-0.5f,0.0f),QVector3D(0.0f,1.0f,0.0f)},     // 右下
        {QVector3D(-0.5f,0.5f,0.0f),QVector3D(0.0f,0.0f,1.0f)},
        {QVector3D(0.5f,0.5f,0.0f),QVector3D(1.0f,0.0f,0.0f)},
        {QVector3D(0.0f,0.0f,0.0f),QVector3D(1.0f,0.0f,0.0f)}
    };

    GLuint indexs[] = {
        0, 1, 2, 3, 4
    };

    VAO.create();
    VAO.bind();

    VBO.create();
    VBO.bind();
    VBO.setUsagePattern(QOpenGLBuffer::StaticDraw);
    VBO.allocate(vertices,5*sizeof(VertexData));

    IBO.create();
    IBO.bind();
    IBO.setUsagePattern(QOpenGLBuffer::StaticDraw);
    IBO.allocate(indexs,5*sizeof(GLuint));

    shaderProgram->setAttributeBuffer(0,GL_FLOAT,0,3,sizeof(VertexData));
    shaderProgram->setAttributeBuffer(1,GL_FLOAT,sizeof(QVector3D),3,sizeof(VertexData));
    shaderProgram->enableAttributeArray(0);
    shaderProgram->enableAttributeArray(1);

    VAO.release();
    VBO.release();
    IBO.release();
    shaderProgram->release();
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    shaderProgram->bind();
    VAO.bind();
    //glDrawArrays(GL_TRIANGLE_STRIP,0,6);      // 这里只根据vertices中的数量来决定画几个三角形
    glDrawElements(GL_TRIANGLE_STRIP,5,GL_UNSIGNED_INT,0);
    VAO.release();
    shaderProgram->release();
}

void GLWidget::initShaders()
{
    shaderProgram = new QOpenGLShaderProgram();

    if(!shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex,":/triangle.vert"))
    {
        qDebug()<<"ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"<<shaderProgram->log()<<endl;
    }
    if(!shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment,":/triangle.frag"))
    {
        qDebug()<<"ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"<<shaderProgram->log()<<endl;
    }

    if(!shaderProgram->link())
    {
        qDebug()<<"ERROR::SHADER::PROGRAM::LINKING_FAILED\n"<<shaderProgram->log()<<endl;
    }

    shaderProgram->bind();
}

void GLWidget::printContextInfo()
{
    QString glType;
    QString glVersion;

    glType = context()->isOpenGLES()?"OpenGL ES":"OpenGL";
    glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));

    qDebug()<<glType<<endl<<glVersion<<endl;
}
