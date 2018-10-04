#include "glwidget.h"

//const char *vertexShaderSource = "#version 330 core\n"
//"layout (location = 0) in vec3 aPos;\n"
//"layout (location = 1) in vec3 aColor;\n"
//"out vec3 ourColor;\n"
//"void main()\n"
//"{\n"
//"   gl_Position = vec4(aPos, 1.0);\n"
//"   ourColor = aColor;\n"
//"}\0";

//const char *fragmentShaderSource = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"in vec3 ourColor;\n"
//"void main()\n"
//"{\n"
//"   FragColor = vec4(ourColor, 1.0f);\n"
//"}\n\0";

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{

}

GLWidget::~GLWidget()
{
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &IBO);
}

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    initShaders();

    // 创建顶点数据
    GLfloat vertices[] = {
        // positions         // colors
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom left
        -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,   // top left
        0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f		// top right
    };

    GLuint indexs[] = {
        0, 1, 2,		// first triangle
        0, 2, 3			// second triangle
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indexs),indexs,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(GLfloat),(GLvoid*)0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(GLfloat),(GLvoid*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    shaderProgram.bind();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
    glBindVertexArray(0);
    shaderProgram.release();
}

void GLWidget::initShaders()
{
//    if(!shaderProgram.addShaderFromSourceCode(QOpenGLShader::Vertex,vertexShaderSource))
//    {
//        qDebug()<<"ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"<<shaderProgram.log()<<endl;
//    }
//    if(!shaderProgram.addShaderFromSourceCode(QOpenGLShader::Fragment,fragmentShaderSource))
//    {
//        qDebug()<<"ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"<<shaderProgram.log()<<endl;
//    }

    if(!shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,":/triangle.vert"))
    {
        qDebug()<<"ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"<<shaderProgram.log()<<endl;
    }
    if(!shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,":/triangle.frag"))
    {
        qDebug()<<"ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"<<shaderProgram.log()<<endl;
    }

    if(!shaderProgram.link())
    {
        qDebug()<<"ERROR::SHADER::PROGRAM::LINKING_FAILED\n"<<shaderProgram.log()<<endl;
    }
}
