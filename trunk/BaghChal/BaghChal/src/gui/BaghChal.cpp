#include "BaghChal.h"
#include "../../ui_BaghChal.h"
#include "QEventLoop"
#include "QFileDialog"
#include "QMessageBox"
#include <iostream>
#include "../logic/FileIO.h"
#include "../logic/Game.h"

//----- temp Variable, ob seit dem letzten Speichern gezogen wurde oder nicht
bool changed = true;
//-------Ende

BaghChal::BaghChal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BaghChal)
{
    ui->setupUi(this);

    ui->turnNotification->setVisible(false);
    ui->statusBar->addPermanentWidget(&statusMsg, 1);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(hideTurnNotification()));
    connect(ui->turnMsgBox, SIGNAL(clicked()), this, SLOT(hideTurnNotification()));

    connect(ui->actionNewGame, SIGNAL(triggered()), this, SLOT(openNewGame()));
    connect(ui->actionLoadGame, SIGNAL(triggered()), this, SLOT(openLoadGame()));
    connect(ui->actionSaveGame, SIGNAL(triggered()), this, SLOT(openSaveGame()));
    connect(ui->actionQuitGame, SIGNAL(triggered()), this, SLOT(openQuitGame()));

    connect(ui->actionHelp, SIGNAL(triggered()), this, SLOT(openHelpWindow()));
    connect(ui->actionInfo, SIGNAL(triggered()), this, SLOT(openInfoWindow()));

    Game *game = Game::getInstance();
    this->game = game;
    setStatusMsg(QString::fromUtf8("Neues Spiel beginnt."));

}

BaghChal* BaghChal::baghchal = 0;
 
BaghChal::~BaghChal()
{
    delete baghchal;
    baghchal = 0;
    delete timer;
    delete ui;
}

BaghChal* BaghChal::getInstance()
{
    if( !baghchal )
    {
        baghchal = new BaghChal(0);
    }
    return baghchal;
}

void BaghChal::closeEvent(QCloseEvent *event)
{
    event->ignore();
    this->openQuitGame();
}

bool BaghChal::askSaveDialog()
{
    QMessageBox askSave;
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/new/Files/icons/Help-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
    askSave.setWindowIcon(icon);

    QLabel qMarkLabel(&askSave);
    qMarkLabel.setObjectName(QString::fromUtf8("qMarkLabel"));
    qMarkLabel.setGeometry(QRect(5, 18, 30, 30));
    qMarkLabel.setFrameShape(QFrame::NoFrame);
    qMarkLabel.setPixmap(QPixmap(QString::fromUtf8(":/new/Files/icons/Help-icon.png")));

    askSave.setText(QString::fromUtf8("\n  Möchten Sie den Spielstand zuvor speichern?\n"));
    QPushButton *saveButton = askSave.addButton(tr("Speichern"),QMessageBox::AcceptRole);
    QPushButton *discardButton = askSave.addButton(tr("Verwerfen"),QMessageBox::DestructiveRole);
    QPushButton *cancelButton = askSave.addButton(tr("Abbrechen"), QMessageBox::RejectRole);
    askSave.setDefaultButton(saveButton);

    askSave.exec();

    if (askSave.clickedButton() == saveButton)
    {
        return openSaveGame();
    }
    else if (askSave.clickedButton() == discardButton)
    {
        return true;
    }
    else if (askSave.clickedButton() == cancelButton)
    {
        return false;
    }
    else
    {
        return false;
    }
}

void BaghChal::openNewGame()
{
    delete game;
    Game::getInstance();
    this->setTurnNotification(0);

}

void BaghChal::openLoadGame()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Spiel laden"), "",
        tr("Text Files (*.txt)"));

    if (filePath != "")
    {
        FileIO file(filePath.toStdString());
        file.loadGame();
    }
}

bool BaghChal::openSaveGame()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Spiel Speichern"), "",
        tr("Text Files (*.txt)"));

    if (fileName != "")
    {
        FileIO file(fileName.toStdString());
        file.saveGame();
        return true;
    }
    else
    {
        return false;
    }
}

void BaghChal::openQuitGame()
{
    this->setStatusMsg(tr("Spiel beenden."));
    if(changed && !askSaveDialog())
    {
        this->clearStatusMsg();
        return;
    }
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

void BaghChal::setStatusMsg(QString msg)
{
    this->statusMsg.setText(msg);
}

void BaghChal::clearStatusMsg()
{
    this->statusMsg.clear();
}

void BaghChal::setTurnNotification(int turn)
{
    switch(turn)
    {
    case 0:
        ui->turnMsg->setText("<font color='White'>Spiel beginnt.</font>");
        setStatusMsg(QString::fromUtf8("Neues Spiel beginnt."));
        break;
    case 1:
        ui->turnMsg->setText("<font color='White'>Ziege ist an der Reihe.</font>");
        setStatusMsg(QString::fromUtf8("Ziege ist an der Reihe."));
        break;
    case 2:
        ui->turnMsg->setText("<font color='White'>Tiger ist an der Reihe.</font>");
        setStatusMsg(QString::fromUtf8("Tiger ist an der Reihe."));
        break;
    case 3:
        ui->turnMsg->setText("<font color='White'>Ziege gewinnt.</font>");
        setStatusMsg(QString::fromUtf8("Ziege gewinnt."));
        break;
    case 4:
        ui->turnMsg->setText("<font color='White'>Tiger gewinnt.</font>");
        setStatusMsg(QString::fromUtf8("Tiger gewinnt."));
        break;
    default:
        return;
    }

    ui->turnNotification->setVisible(true);
    timer->start(3000);
}

void BaghChal::hideTurnNotification()
{
    timer->stop();
    ui->turnNotification->setVisible(false);
}

void BaghChal::showTurnArrow(int turn)
{
    switch(turn)
    {
    case 0:
        ui->arrowGoat->hide();
        ui->arrowTiger->hide();
        break;
    case 1:
        ui->arrowGoat->show();
        ui->arrowTiger->hide();
        break;
    case 2:
        ui->arrowGoat->hide();
        ui->arrowTiger->show();
        break;
    default:
        break;
    }
}
