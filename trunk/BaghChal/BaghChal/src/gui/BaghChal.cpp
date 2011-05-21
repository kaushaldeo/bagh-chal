#include "BaghChal.h"
#include "../../ui_BaghChal.h"
#include "QEventLoop"
#include "QFileDialog"
#include "QMessageBox"
#include <iostream>
#include "../logic/FileIO.h"
#include "../logic/Game.h"
#include "../logic/Cell.h"
#include <iterator>

using namespace baghchal;


//----- temp Variable, ob seit dem letzten Speichern gezogen wurde oder nicht
bool changed = true;
//-------Ende

BaghChal::BaghChal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BaghChal)
{
    ui->setupUi(this);

    Game *game = Game::getInstance();
    this->game = game;

    ui->turnNotification->setVisible(false);
    ui->statusBar->addPermanentWidget(&statusMsg, 1);
    this->showTurnArrowAndMessage(goat);
    setStatusMsg(QString::fromUtf8("Neues Spiel beginnt."));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(hideTurnNotification()));
    connect(ui->turnMsgBox, SIGNAL(clicked()), this, SLOT(hideTurnNotification()));

    connect(ui->actionNewGame, SIGNAL(triggered()), this, SLOT(openNewGame()));
    connect(ui->actionLoadGame, SIGNAL(triggered()), this, SLOT(openLoadGame()));
    connect(ui->actionSaveGame, SIGNAL(triggered()), this, SLOT(openSaveGame()));
    connect(ui->actionQuitGame, SIGNAL(triggered()), this, SLOT(openQuitGame()));

    connect(ui->actionHelp, SIGNAL(triggered()), this, SLOT(openHelpWindow()));
    connect(ui->actionInfo, SIGNAL(triggered()), this, SLOT(openInfoWindow()));


    boxes.insert(ui->box_00);
    boxes.insert(ui->box_01);
    boxes.insert(ui->box_02);
    boxes.insert(ui->box_03);
    boxes.insert(ui->box_04);
    boxes.insert(ui->box_10);
    boxes.insert(ui->box_11);
    boxes.insert(ui->box_12);
    boxes.insert(ui->box_13);
    boxes.insert(ui->box_14);
    boxes.insert(ui->box_20);
    boxes.insert(ui->box_21);
    boxes.insert(ui->box_22);
    boxes.insert(ui->box_23);
    boxes.insert(ui->box_24);
    boxes.insert(ui->box_30);
    boxes.insert(ui->box_31);
    boxes.insert(ui->box_32);
    boxes.insert(ui->box_33);
    boxes.insert(ui->box_34);
    boxes.insert(ui->box_40);
    boxes.insert(ui->box_41);
    boxes.insert(ui->box_42);
    boxes.insert(ui->box_43);
    boxes.insert(ui->box_44);

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
    Game *game = Game::getInstance();
    this->game = game;
    this->renderGame();
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
        this->renderGame();
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
        ui->turnMsg->setText("<font color='White'>Tiger ist an der Reihe.</font>");
        setStatusMsg(QString::fromUtf8("Tiger ist an der Reihe."));
        break;
    case 2:
        ui->turnMsg->setText("<font color='White'>Ziege ist an der Reihe.</font>");
        setStatusMsg(QString::fromUtf8("Ziege ist an der Reihe."));
        break;
    case 3:
        ui->turnMsg->setText("<font color='White'>Ziege gewinnt.</font>");
        setStatusMsg(QString::fromUtf8("Ziege gewinnt."));
        break;
    case 4:
        ui->turnMsg->setText("<font color='White'>Tiger gewinnt.</font>");
        setStatusMsg(QString::fromUtf8("Tiger gewinnt."));
        break;
    case 5:
        ui->turnMsg->setText("<font color='White'>Unentschieden. Keine weitere Züge möglich.</font>");
        setStatusMsg(QString::fromUtf8("Unentschieden. Keine weitere Züge möglich."));
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

void BaghChal::showTurnArrowAndMessage(int turn)
{
    switch(turn)
    {
    case empty:
        ui->arrowGoat->hide();
        ui->arrowTiger->hide();
        break;
    case tiger:
        ui->arrowGoat->hide();
        ui->arrowTiger->show();
        setStatusMsg(QString::fromUtf8("Tiger ist an der Reihe."));
        Game::getInstance()->setTurn(tiger);
        break;
    case goat:
        ui->arrowGoat->show();
        ui->arrowTiger->hide();
        setStatusMsg(QString::fromUtf8("Ziege ist an der Reihe."));
        game->setTurn(goat);
        break;
    default:
        break;
    }
}

void BaghChal::renderGame()
{
    //reset outer avatars
    for (int i = 0; i < 20; i++)
    {
        QString preString = "";
        if ( i < 10 )
        {
            preString = "0";
        }
        QWidget *outerBox = qFindChild<QWidget*>(this, "unusedGoat_" + preString + QString::number(i));
        if (outerBox)
        {
            AvatarWidget *oldAvatar = outerBox->findChild<AvatarWidget*>();
            if( oldAvatar )
            {
                delete oldAvatar;
            }
        }
    }
    
    //set avatars outer grid
    int nextGoats = game->getGoat().getNextGoat();
    nextGoats = 20 - nextGoats;
    for (int i = 0; i < nextGoats; i++)
    {
        QString preString = "";
        if ( i < 10 )
        {
            preString = "0";
        }
        QWidget *outerBox = qFindChild<QWidget*>(this, "unusedGoat_" + preString + QString::number(i));
        if (outerBox)
        {
            AvatarWidget* goat = new AvatarWidget( outerBox );
            goat->setObjectName(QString::fromUtf8("goat"));
            goat->setGeometry(QRect(0, 0, 41, 41));
            goat->setCursor(QCursor(Qt::ArrowCursor));
            goat->setProperty("goat", QVariant(true));
            goat->show();
            QLabel* goatImage = new QLabel(goat);
            goatImage->setObjectName(QString::fromUtf8("goatImage"));
            goatImage->setGeometry(QRect(0, 0, 41, 41));
            goatImage->setPixmap(QPixmap(QString::fromUtf8(":/new/Files/icons/spielfigur_ziege.png")));
            goatImage->show();
        }
    }
    
    set<BoxWidget*>::iterator it;
    //reset avatars in grid
    for( it = boxes.begin(); it != boxes.end(); ++it )
    {
        foreach(QWidget *widget, (*it)->findChildren<QWidget*>())
        {
            widget->close();
        }
        (*it)->setAcceptDrops(1);
    }
    
    //set avatars in grid
    for( it = boxes.begin(); it != boxes.end(); ++it )
    {
        (*it)->placeAvatar();
    }
    
    //call a method to place eaten goats
    (*boxes.begin())->placeGoatInRippedField( game->getTiger().getScore() );
    
    //show message
    this->showTurnArrowAndMessage( game->getTurn() );
}
