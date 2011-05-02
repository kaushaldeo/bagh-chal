#include "BaghChal.h"
#include "../../ui_BaghChal.h"
#include "QEventLoop"
#include "QFileDialog"
#include "QMessageBox"
#include "QTextStream"
#include <iostream>

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

}

BaghChal::~BaghChal()
{
    delete timer;
    delete ui;
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

    askSave.setText("\n  Möchten Sie den Spielstand zuvor speichern ?\n");
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
    this->setTurnNotification(0);
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

bool BaghChal::openSaveGame()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Spiel Speichern"), "",
        tr("Text Files (*.txt)"));

    if (fileName != "")
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly))
          return false;

        QTextStream stream(&file);
         //------------ Test String Ausgabe
         stream << "hallo" << "\n" << "Simon, hallo Steffen";
         //------------ ENDE

        file.close();
        return true;
    }
    else
    {
        return false;
    }
}

void BaghChal::openQuitGame()
{
    this->setStatusMsg(tr("Spiel beenden"));
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
        ui->turnMsg->setText("<font color='White'>Spiel beginnt</font>");
        break;
    case 1:
        ui->turnMsg->setText("<font color='White'>Spieler 1 ist an der Reihe</font>");
        break;
    case 2:
        ui->turnMsg->setText("<font color='White'>Spieler 2 ist an der Reihe</font>");
        break;
    case 3:
        ui->turnMsg->setText("<font color='White'>Spieler 1 gewinnt</font>");
        break;
    case 4:
        ui->turnMsg->setText("<font color='White'>Spieler 2 gewinnt</font>");
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
