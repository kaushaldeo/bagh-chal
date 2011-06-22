/**
 * BaghChal class
 * @file BaghChal.cpp
 * @brief Implementation for BaghChal Class
 * @see BaghChal
 * @author Mirko Indlekofer
 */

#include "QEventLoop"
#include "QFileDialog"
#include "QMessageBox"

#include "BaghChal.h"
#include "../logic/Cell.h"
#include "../logic/FileIO.h"
#include "../logic/Game.h"
#include "../../ui_BaghChal.h"

#include <iterator>

using namespace baghchal;

/**
 * @fn BaghChal()
 * @brief Constructor
 * @param parent - The parent QWidget element
 *
 * This function sets up the UI and creates an instance of the class Game. It also connects all menue items to their corresponding slots.
 * Every object of the BoxWidget class are added to a list.
 */
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

/**
 * Setting Singleton baghchal to NULL
 */
BaghChal *BaghChal::baghchal = 0;

/**
 * @fn ~BaghChal()
 * @brief Destructor
 * 
 * Deletes timer, ui and baghchal, and sets singleton baghchal to NULL
 */
BaghChal::~BaghChal()
{
    delete baghchal;
    baghchal = 0;
    delete timer;
    delete ui;
}

/**
 * @fn getInstance()
 * @brief Returns the singleton baghchal
 *
 * Creates a singleton, if it doesn't already exist, and returns the singleton.
 */
BaghChal *BaghChal::getInstance()
{
    if (!baghchal)
    {
        baghchal = new BaghChal(0);
    }

    return baghchal;
}

/**
 * @fn getBoxes()
 * @brief Returns a list containing all objects of the Boxwidget class
 * @return list<BoxWidget *> 
 *
 * Returns a list containing all objects of the BoxWidget class.
 */
list<BoxWidget *> BaghChal::getBoxes()
{
    return boxes;
}

/**
 * @fn closeEvent()
 * @brief The close event from Qt
 * @param event - QCloseEvent value
 * @see openQuitGame()
 *
 * This function is called, when the user clicks on the close button of the window (the 'X' button).
 * This function simply ignores the QCloseEvent and calls the openQuitGame() function to avoid closing the game without showing the save game dialogue.
 */
void BaghChal::closeEvent(QCloseEvent *event)
{
    event->ignore();
    this->openQuitGame();
}

/**
 * @fn askSaveDialog()
 * @brief Opens the save game dialogue
 * @see openSaveGame()
 * @return bool
 *
 * Opens the save game dialogue and returns if the game was saved or not. Calls openSaveGame() if the user wants to save.
 */
bool BaghChal::askSaveDialog()
{
    QMessageBox askSave;
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/new/Files/icons/Help-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
    askSave.setWindowIcon(icon);

    QLabel askImage(&askSave);
    askImage.setObjectName(QString::fromUtf8("askImage"));
    askImage.setGeometry(QRect(5, 18, 30, 30));
    askImage.setFrameShape(QFrame::NoFrame);
    askImage.setPixmap(QPixmap(QString::fromUtf8(":/new/Files/icons/Help-icon.png")));

    askSave.setText(QString::fromUtf8("\n  Möchten Sie den Spielstand zuvor speichern?\n"));
    QPushButton *saveButton = askSave.addButton(tr("Speichern"), QMessageBox::AcceptRole);
    QPushButton *discardButton = askSave.addButton(tr("Verwerfen"), QMessageBox::DestructiveRole);
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

/**
 * @fn openNewGame()
 * @brief Opens a new game
 * @see askSaveDialog()
 *
 * If the current game was changed the save game dialogue opens. If the game was successfully saved or discarded, the function creates a new game.
 */
void BaghChal::openNewGame()
{
    this->setStatusMsg(tr("Neues Spiel starten."));

    if (this->game->getChanged() && !askSaveDialog())
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

/**
 * @fn openLoadGame()
 * @brief Opens the Load Game Dialogue
 * @see loadGame()
 * @see renderGame()
 *
 * Opens the load game dialogue and calls the function loadGame() to load a saved game into the logical layer. After loading the game it calls the renderGame() function to set up the game.
 */
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
            showMessage(NotificationWithTimer, QString::fromUtf8("Spiel geladen."));
        }
        catch (OccupiedCellException *e)
        {
            showMessage(NotificationWithoutTimer, QString::fromUtf8(e->what()));
        }
        catch (InvalidInputFileException *e)
        {
            showMessage(NotificationWithoutTimer, QString::fromUtf8(e->what()));
        }
        catch (InvalidStateException *e)
        {
            showMessage(NotificationWithoutTimer, QString::fromUtf8(e->what()));
        }
    }
}

/**
 * @fn openSaveGame()
 * @brief Opens the save game dialogue
 * @see saveGame()
 * @return bool
 *
 * Opens the save game dialogue and calls the function saveGame() to create a save game file. Return if the game was successfully saved or not.
 */
bool BaghChal::openSaveGame()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Spiel Speichern"), "",
                       tr("Text Files (*.txt)"));

    if (fileName != "")
    {
        FileIO file(fileName.toStdString());
        try
        {
            file.saveGame();
            showMessage(NotificationWithTimer, QString::fromUtf8("Spiel gespeichert."));
            return true;
        }
        catch (exception)
        {
            showMessage(NotificationWithTimer, QString::fromUtf8("Speichern fehlgeschlagen."));
            return false;
        }
    }
    else
    {
        return false;
    }
}

/**
 * @fn openQuitGame()
 * @brief Quits the Game
 * @see askSaveDialog()
 *
 * Calls the askSaveDialog() function to ask if the game should be saved before it quits the game.
 */
void BaghChal::openQuitGame()
{
    this->setStatusMsg(tr("Spiel beenden."));

    if (this->game->getChanged() && !askSaveDialog())
    {
        this->clearStatusMsg();
        return;
    }

    qApp->quit();
}

/**
 * @fn openHelpWindow()
 * @brief Opens the Help Window
 *
 * This function opens the help window.
 */
void BaghChal::openHelpWindow()
{
    hw.show();
    hw.raise();

    QEventLoop loop;
    loop.exec();
}

/**
 * @fn openInfoWindow()
 * @brief Opens the Info Window
 *
 * This funktion opens the info window.
 */
void BaghChal::openInfoWindow()
{
    iw.show();
    iw.raise();

    QEventLoop loop;
    loop.exec();
}

/**
 * @fn setStatusMsg
 * @brief Sets the message of the statusbar
 * @param msg - The message for the statusbar
 *
 * This function sets the statusbar message to the string which is passed by the parameter.
 */
void BaghChal::setStatusMsg(QString msg)
{
    this->statusMsg.setText(msg);
}

/**
 * @fn clearStatusMsg()
 * @brief Clears the status message
 *
 * This function clears the content of the statusbar.
 */
void BaghChal::clearStatusMsg()
{
    this->statusMsg.clear();
}

/**
 * @fn showMessage()
 * @brief Shows a Message Notification
 * @param messageCase - The case, if message is a notification, a statusbar message or both of them
 * @param msg - Content of the message as a string
 *
 * Shows a message as a notification or as a statusbar message or both of them with and without timer.
 */
void BaghChal::showMessage(MessageState messageCase, QString msg)
{
    switch (messageCase)
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

/**
 * @fn hideTurnNotification
 * @brief Makes the turn notification disappear
 *
 * If the game did not end, the turn notification can disappear. Otherwise, if the game did end, it is not possible to let the turn notification disappear.
 */
void BaghChal::hideTurnNotification()
{
    if (this->game->getTurn() != 0)
    {
        timer->stop();
        ui->turnNotification->setVisible(false);
    }
}

/**
 * @fn showTurnArrowAndMessage
 * @brief Shows, whose turn is it.
 * @param turn - int value containing, whose turn is it
 * @see showMessage
 *
 * Shows the arrow and the statusbar message, which notifies whose turn is it.
 */
void BaghChal::showTurnArrowAndMessage(int turn)
{
    switch (turn)
    {
    case empty:
        ui->arrowGoat->hide();
        ui->arrowTiger->hide();
        break;
    case tiger:
        ui->arrowGoat->hide();
        ui->arrowTiger->show();
        this->showMessage(OnlyStatusBar, QString::fromUtf8("Tiger ist an der Reihe."));
        break;
    case goat:
        ui->arrowGoat->show();
        ui->arrowTiger->hide();
        this->showMessage(OnlyStatusBar, QString::fromUtf8("Ziege ist an der Reihe."));
        break;
    default:
        break;
    }
}

/**
 * @fn renderGame()
 * @brief Sets up a saved Game
 * @see placeGoatInRippedField()
 * @see showTurnArrowAndMessage()
 *
 * Setting up a saved game, after loading it into the logical layer. After resetting the current game, all the avatars are placed on their correct position in the playing field.
 */
void BaghChal::renderGame()
{
    //reset outer avatars
    for (int i = 0; i < 20; i++)
    {
        QString preString = "";

        if (i < 10)
        {
            preString = "0";
        }

        QWidget *outerBox = qFindChild<QWidget *>(this, "unusedGoat_" + preString + QString::number(i));

        if (outerBox)
        {
            AvatarWidget *oldAvatar = outerBox->findChild<AvatarWidget *>();

            if (oldAvatar)
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

        if (i < 10)
        {
            preString = "0";
        }

        QWidget *outerBox = qFindChild<QWidget *>(this, "unusedGoat_" + preString + QString::number(i));

        if (outerBox)
        {
            //create new goat widget as AvatarWidget
            AvatarWidget *goat = new AvatarWidget(outerBox);
            goat->setObjectName(QString::fromUtf8("goat"));
            goat->setGeometry(QRect(0, 0, 51, 51));
            goat->setCursor(QCursor(Qt::ArrowCursor));
            goat->setProperty("goat", QVariant(true));

            //create goat image as QLabel
            QLabel *goatImage = new QLabel(goat);
            goatImage->setObjectName(QString::fromUtf8("goatImage"));
            goatImage->setGeometry(QRect(0, 0, 41, 41));
            goatImage->setPixmap(QPixmap(QString::fromUtf8(":/new/Files/icons/spielfigur_ziege.png")));

            //show goat
            goat->show();
            goatImage->show();
        }
    }

    list<BoxWidget *>::iterator it;

    //reset avatars in grid
    for (it = boxes.begin(); it != boxes.end(); ++it)
    {
        foreach(QWidget * widget, (*it)->findChildren<QWidget *>())
        {
            widget->close();
        }
        (*it)->setAcceptDrops(1);
    }

    //set avatars in grid
    for (it = boxes.begin(); it != boxes.end(); ++it)
    {
        //reset mapping cell to grid
        (*it)->setCell(NULL);
        (*it)->placeAvatar();
    }

    //reset eaten goats
    for (int i = 0; i < 5; ++i)
    {
        QWidget *rippedField = qFindChild<QWidget *>(this, "rippedGoat_0" + QString::number(i));
        QLabel *label = rippedField->findChild<QLabel *>();

        if (label)
        {
            delete label;
        }
    }

    //place eaten goats
    (*boxes.begin())->placeGoatInRippedField(game->getTiger().getScore());

    //show message
    this->showTurnArrowAndMessage(game->getTurn());
}
