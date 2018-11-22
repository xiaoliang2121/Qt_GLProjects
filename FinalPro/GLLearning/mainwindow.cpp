#include "mainwindow.h"

GLfloat blockSize = 0.1f;
GLfloat vVerts[] = { -blockSize, -blockSize, 0.0f,
                      blockSize, -blockSize, 0.0f,
                      blockSize,  blockSize, 0.0f,
                     -blockSize,  blockSize, 0.0f};

MainWindow::MainWindow()
{
    vao = new QOpenGLVertexArrayObject;
    vbo = new QOpenGLBuffer;
    ibo = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
}

MainWindow::~MainWindow()
{
    makeCurrent();
    vao->destroy();
    vbo->destroy();
    ibo->destroy();
    doneCurrent();
}

void MainWindow::initializeGL()
{
    initializeOpenGLFunctions();

    // 初始化
    initShaders();

    glClearColor(0.0f,0.0f,1.0f,1.0f);

    GLuint indexs[] = {
        0,1,2,
        0,2,3
    };

    program.bind();
    vao->create();
    vao->bind();
        vbo->create();
        vbo->bind();
        vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);
        vbo->allocate(vVerts,sizeof(vVerts));

        ibo->create();
        ibo->bind();
        ibo->setUsagePattern(QOpenGLBuffer::StaticDraw);
        ibo->allocate(indexs,sizeof(indexs));

        program.setAttributeBuffer(0,GL_FLOAT,0,3,3*sizeof(GLfloat));
        program.enableAttributeArray(0);

    vao->release();
    ibo->release();
    vbo->release();
    program.release();
}

void MainWindow::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}

void MainWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    program.bind();
    vao->bind();

    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

    vao->release();
    program.release();

    // 测试裁剪
//    glEnable(GL_SCISSOR_TEST);

//    glClearColor(1.0f,0.0f,0.0f,1.0f);
//    glScissor(100,100,600,400);
//    glClear(GL_COLOR_BUFFER_BIT);

//    glClearColor(0.0f,1.0f,0.0f,1.0f);
//    glScissor(200,200,400,200);
//    glClear(GL_COLOR_BUFFER_BIT);

//    glDisable(GL_SCISSOR_TEST);

}

void MainWindow::keyPressEvent(QKeyEvent *ev)
{
    GLfloat stepSize = 0.025f;

    GLfloat blockX = vVerts[0];
    GLfloat blockY = vVerts[7];

    if(ev->key() == Qt::Key_Up)
        blockY += stepSize;

    if(ev->key() == Qt::Key_Down)
        blockY -= stepSize;

    if(ev->key() == Qt::Key_Left)
        blockX -= stepSize;

    if(ev->key() == Qt::Key_Right)
        blockX += stepSize;

    // 边界检测
    if(blockX < -1.0f)
        blockX = -1.0f;

    if(blockX > (1.0f-blockSize*2))
        blockX = 1.0f -blockSize*2;

    if(blockY < (-1.0f+2*blockSize))
        blockY = -1.0f + blockSize*2;

    if(blockY > 1.0f)
        blockY = 1.0f;

    // 重新计算顶点位置
    vVerts[0] = blockX;
    vVerts[1] = blockY - blockSize*2;

    vVerts[3] = blockX + blockSize*2;
    vVerts[4] = blockY - blockSize*2;

    vVerts[6] = blockX + blockSize*2;
    vVerts[7] = blockY;

    vVerts[9] = blockX;
    vVerts[10] = blockY;

    program.bind();
    vao->bind();
    vbo->bind();
        program.disableAttributeArray(0);
        vbo->allocate(vVerts,sizeof(vVerts));
        program.enableAttributeArray(0);
    vbo->release();
    vao->release();
    program.release();

    update();
}

void MainWindow::initShaders()
{
    // 输入文件要是utf-8 无bom格式
    if(!program.addShaderFromSourceFile(QOpenGLShader::Vertex,":/shaders/shader.vert"))
    {
        qDebug()<<"ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"<<program.log()<<endl;
    }
    if(!program.addShaderFromSourceFile(QOpenGLShader::Fragment,":/shaders/shader.frag"))
    {
        qDebug()<<"ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"<<program.log()<<endl;
    }

    if(!program.link())
    {
        qDebug()<<"ERROR::SHADER::PROGRAM::LINKING_FAILED\n"<<program.log()<<endl;
    }
}
