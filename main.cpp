#include "qfaracam.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFaraCam w;
    w.show();

    return a.exec();
}
