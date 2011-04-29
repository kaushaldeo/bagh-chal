#include "BaghChal.h"
#include "../../ui_BaghChal.h"
#include "QEventLoop"
#include "QFileDialog"
#include "QMessageBox"
#include "QTextStream"
#include <iostream>

BaghChal::BaghChal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BaghChal)
{
    ui->setupUi(this);

    connect(ui->actionLoadGame, SIGNAL(triggered()), this, SLOT(openLoadGame()));
    connect(ui->actionSaveGame, SIGNAL(triggered()), this, SLOT(openSaveGame()));
    connect(ui->actionQuitGame, SIGNAL(triggered()), this, SLOT(openQuitGame()));

    connect(ui->actionHelp, SIGNAL(triggered()), this, SLOT(openHelpWindow()));
    connect(ui->actionInfo, SIGNAL(triggered()), this, SLOT(openInfoWindow()));

}

BaghChal::~BaghChal()
{
    delete ui;
}

void BaghChal::openLoadGame()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Spiel laden"), "",
        tr("Text Files (*.txt)"));

    if (filePath != "")
    {
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly))
        {
            return;
        }
        QString text = file.readAll();

        //----- Test String Ausgabe
        QMessageBox::information(this, tr("Info"), text);
        //----- ENDE

        file.close();
    }
}

void BaghChal::openSaveGame()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Spiel Speichern"), "",
        tr("Text Files (*.txt)"));

    if (fileName != "")
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)| QIODevice::Text)
          return;

        QTextStream stream(&file);
        stream << "hallo" << "\n" << "Simon";
        file.close();

    }
}

void BaghChal::openQuitGame()
{
    qApp->quit();
}

void BaghChal::openHelpWindow()
{
    hw.show();
    hw.raise();

    QEventLoop loop;
    loop.exec();
}

void BaghChal::openInfoWindow()
{
    iw.show();
    iw.raise();

    QEventLoop loop;
    loop.exec();
}
