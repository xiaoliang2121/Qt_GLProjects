#include <QGuiApplication>
#include "glwindow.h"

int main(int argc,char *argv[])
{
    QGuiApplication app(argc,argv);

    GLWindow window;
    window.resize(800,600);
    window.show();

    return app.exec();
}
