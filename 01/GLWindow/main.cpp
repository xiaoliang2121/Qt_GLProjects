#include <QGuiApplication>
#include "glwindow.h"

int main(int argc,char *argv[])
{
    QGuiApplication app(argc,argv);

    QSurfaceFormat format;
    format.setProfile(QSurfaceFormat::CompatibilityProfile);
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);

    GLWindow window;
    window.setFormat(format);
    window.resize(800,600);
    window.show();

    return app.exec();
}
