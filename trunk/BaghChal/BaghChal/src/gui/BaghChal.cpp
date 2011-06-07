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

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(hideTurnNotification()));
    connect(ui->turnMsgBox, SIGNAL(clicked()), this, SLOT(hideTurnNotification()));

    connect(ui->actionNewGame, SIGNAL(triggered()), this, SLOT(openNewGame()));
    connect(ui->actionLoadGame, SIGNAL(triggered()), this, SLOT(openLoadGame()));
    connect(ui->actionSaveGame, SIGNAL(triggered()), this, SLOT(openSaveGame()));
    connect(ui->actionQuitGame, SIGNAL(triggered()), this, SLOT(openQuitGame()));

    connect(ui->actionHelp, SIGNAL(triggered()), this, SLOT(openHelpWindow()));
    connect(ui->actionInfo, SIGNAL(triggered()), this, SLOT(openInfoWindow()));


    boxes.push_back(ui->box_00);
    boxes.push_back(ui->box_01);
    boxes.push_back(ui->box_02);
    boxes.push_back(ui->box_03);
    boxes.push_back(ui->box_04);
    boxes.push_back(ui->box_10);
    boxes.push_back(ui->box_11);
    boxes.push_back(ui->box_12);
    boxes.push_back(ui->box_13);
    boxes.push_back(ui->box_14);
    boxes.push_back(ui->box_20);
    boxes.push_back(ui->box_21);
    boxes.push_back(ui->box_22);
    boxes.push_back(ui->box_23);
    boxes.push_back(ui->box_24);
    boxes.push_back(ui->box_30);
    boxes.push_back(ui->box_31);
    boxes.push_back(ui->box_32);
    boxes.push_back(ui->box_33);
    boxes.push_back(ui->box_34);
    boxes.push_back(ui->box_40);
    boxes.push_back(ui->box_41);
    boxes.push_back(ui->box_42);
    boxes.push_back(ui->box_43);
    boxes.push_back(ui->box_44);

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

list<BoxWidget*> BaghChal::getBoxes()
{
    return boxes;
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
    this->setStatusMsg(tr("Neues Spiel starten."));
    if(this->game->getChanged() && !askSaveDialog())
    {
        this->clearStatusMsg();
        return;
    }

    delete game;
    Game *game = Game::getInstance();
    this->game = game;
    this->renderGame();
    this->showMessage(NotificationWithTimer, QString::fromUtf8("Spiel beginnt."));
    QApplication::restoreOverrideCursor();
}

void BaghChal::openLoadGame()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Spiel laden"), "",
        tr("Text Files (*.txt)"));

    if (filePath != "")
    {
        FileIO file(filePath.toStdString());
        try
        {
            file.loadGame();
            this->renderGame();
        }
        catch( OccupiedCellException *e )
        {
            showMessage(NotificationWithoutTimer, QString::fromUtf8( e->what() ));
        }
        catch( InvalidInputFileException *e )
        {
            showMessage(NotificationWithoutTimer, QString::fromUtf8( e->what() ));
        }
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
    if(this->game->getChanged() && !askSaveDialog())
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

void BaghChal::showMessage(int caseNumber, QString msg)
{
    switch(caseNumber)
    {
    //case 0: only statusbar
    case OnlyStatusBar:
        this->setStatusMsg(msg);
        return;
    //case 1: only notification with timer
    case OnlyNotification:
        ui->turnMsg->setText("<font color='White'>" + msg + "</font>");
        timer->start(3000);
        break;
    //case 2: notification and statusbar with timer
    case NotificationWithTimer:
        ui->turnMsg->setText("<font color='White'>" + msg + "</font>");
        this->setStatusMsg(msg);
        timer->start(3000);
        break;
    //case 3: notification and statusbar without timer -> game has ended.
    case NotificationWithoutTimer:
        ui->turnMsg->setText("<font color='White'>" + msg + "</font>");
        setStatusMsg(msg);
        QApplication::setOverrideCursor(QCursor(Qt::ArrowCursor));
        break;
    default:
        return;
    }

    ui->turnNotification->setVisible(true);
}

void BaghChal::hideTurnNotification()
{
    if(this->game->getTurn()!= 0)
    {
        timer->stop();
        ui->turnNotification->setVisible(false);
    }
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
        this->showMessage(OnlyStatusBar,QString::fromUtf8("Tiger ist an der Reihe."));
        break;
    case goat:
        ui->arrowGoat->show();
        ui->arrowTiger->hide();
        this->showMessage(OnlyStatusBar,QString::fromUtf8("Ziege ist an der Reihe."));
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
                oldAvatar->close();
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
            //create new goat widget as AvatarWidget
            AvatarWidget* goat = new AvatarWidget( outerBox );
            goat->setObjectName(QString::fromUtf8("goat"));
            goat->setGeometry(QRect(0, 0, 51, 51));
            goat->setCursor(QCursor(Qt::ArrowCursor));
            goat->setProperty("goat", QVariant(true));
            
            //create goat image as QLabel
            QLabel* goatImage = new QLabel(goat);
            goatImage->setObjectName(QString::fromUtf8("goatImage"));
            goatImage->setGeometry(QRect(0, 0, 41, 41));
            goatImage->setPixmap(QPixmap(QString::fromUtf8(":/new/Files/icons/spielfigur_ziege.png")));
            
            //show goat
            goat->show();
            goatImage->show();
        }
    }
    
    list<BoxWidget*>::iterator it;
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
        //reset mapping cell to grid
        (*it)->setCell(NULL);
        (*it)->placeAvatar();
    }
        
    //call a method to place or reset eaten goats
    (*boxes.begin())->placeGoatInRippedField( game->getTiger().getScore() );
    
    //show message
    this->showTurnArrowAndMessage( game->getTurn() );
}
