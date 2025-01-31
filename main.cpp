#include <QtGui/QGuiApplication>
#include "glcomputespace.h"

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

    GLComputeSpace space;
    space.init();
    space.start();

    return 0;
}
