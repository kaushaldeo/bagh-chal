#include "BaghChal.h"
#include "helpWindow.h"
#include "../../ui_BaghChal.h"
#include "QEventLoop"

BaghChal::BaghChal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BaghChal)
{
    ui->setupUi(this);
    connect(ui->actionHelp, SIGNAL(triggered()), this, SLOT(openHelpWindow()));
    connect(ui->actionQuitGame,SIGNAL (triggered()), qApp, SLOT(quit()));
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
