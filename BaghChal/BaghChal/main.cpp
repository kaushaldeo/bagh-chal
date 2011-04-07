#include <QtGui/QApplication>
#include "BaghChal.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BaghChal w;
    w.show();

    return a.exec();
}
