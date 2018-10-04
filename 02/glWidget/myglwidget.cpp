#include "myglwidget.h"
#include <QOpenGLFunctions>
#include <QOpenGLContext>
#include <QDebug>

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

MyGLWidget::MyGLWidget(QWidget *parent):
    QOpenGLWidget(parent)
{

}

void MyGLWidget::initializeGL()
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClearColor(0.0f,1.0f,0.0f,1.0f);

    // vertex shader
    int vertexShader = f->glCreateShader(GL_VERTEX_SHADER);
    f->glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    f->glCompileShader(vertexShader);
    // check for compile errors
    int success;
    char infoLog[512];
    f->glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
    if(!success)
    {
        f->glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
        qDebug()<< "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
    }

    // fragment shader
    int fragmentShader = f->glCreateShader(GL_FRAGMENT_SHADER);
    f->glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
    f->glCompileShader(fragmentShader);
    // check for compile errors
    f->glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);
    if(!success)
    {
        f->glGetShaderInfoLog(fragmentShader,512,NULL,infoLog);
        qDebug()<< "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
    }

    // link shaders
    int shaderProgram = f->glCreateProgram();
    f->glAttachShader(shaderProgram,vertexShader);
    f->glAttachShader(shaderProgram,fragmentShader);
    f->glLinkProgram(shaderProgram);
    // check for link errors
    f->glGetProgramiv(shaderProgram,GL_LINK_STATUS,&success);
    if(!success)
    {
        f->glGetProgramInfoLog(shaderProgram,512,NULL,infoLog);
        qDebug()<< "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
    }
    f->glDeleteShader(vertexShader);
    f->glDeleteShader(fragmentShader);

    // 设置顶点数据和配置顶点属性
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    uint VBO,VAO;

}

void MyGLWidget::resizeGL(int w, int h)
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glViewport(0,0,w,h);
}

void MyGLWidget::paintGL()
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClear(GL_COLOR_BUFFER_BIT);
}
