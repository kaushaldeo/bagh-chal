#include <QtGui/QApplication>
#include "src/gui/BaghChal.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BaghChal *baghchal = BaghChal::getInstance();
    baghchal->show();

    return a.exec();
}
