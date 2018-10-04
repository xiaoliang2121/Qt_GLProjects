#include <QApplication>
#include "myglwidget.h"
#include "dialog.h"

int main(int argc,char* argv[])
{
    QApplication app(argc,argv);

    QSurfaceFormat format;
    format.setVersion(3,3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    Dialog w;
    w.resize(800,600);
    w.show();

    return app.exec();
}
