/**
* Main method
* @file main.cpp
* @brief The main program
* @author Simon Schneeberger
*
* This starts QApplication and shows the BaghChal QMainWindow.
*/

#include <QtGui/QApplication>
#include "src/gui/BaghChal.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BaghChal *baghchal = BaghChal::getInstance();
    baghchal->show();

    return a.exec();
}
