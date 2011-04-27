#include "BaghChal.h"
#include "helpWindow.h"
#include "infoWindow.h"
#include "../../ui_BaghChal.h"
#include "QEventLoop"

BaghChal::BaghChal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BaghChal)
{
    ui->setupUi(this);

    connect(ui->actionQuitGame,SIGNAL (triggered()), qApp, SLOT(quit()));

    connect(ui->actionHelp, SIGNAL(triggered()), this, SLOT(openHelpWindow()));
    connect(ui->actionInfo, SIGNAL(triggered()), this, SLOT(openInfoWindow()));

}

BaghChal::~BaghChal()
{
    delete ui;
}

void BaghChal::openHelpWindow()
{
    HelpWindow w;
    w.show();

    QEventLoop loop;
    loop.exec();
}

void BaghChal::openInfoWindow()
{
    InfoWindow w;
    w.show();

    QEventLoop loop;
    loop.exec();
}
