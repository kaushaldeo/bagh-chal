/**
 * BaghChal Class
 * @file BaghChal.h
 * @brief Headerfile for BaghChal Class
 * @see BaghChal
 * @author Mirko Indlekofer
 */

#ifndef BAGHCHAL_H
#define BAGHCHAL_H

#include <QMainWindow>
#include "QCloseEvent"
#include "helpWindow.h"
#include "infoWindow.h"
#include "QTimer"
#include "../logic/Game.h"
#include <list>
#include "boxWidget.h"
#include <QDebug>


namespace Ui
{
class BaghChal;
}

/**
 * @brief Enumeration for the state of a message
 */
enum MessageState
{
    OnlyStatusBar,              /**< Only a Statusbar Message */
    OnlyNotification,           /**< Notification with timer */
    NotificationWithTimer,      /**< Notification and Statusbar Message with timer */
    NotificationWithoutTimer    /**< Notification ans Statusbar Message without timer */
};

/**
 * @class BaghChal
 * @brief Derived Class of QMainWindow for the Mainwindow
 *
 * The BaghChal Class represents the GUI of the Game as a derived class of QMainWindow including a Menuebar, a Statusbar and several QWidgets.
 */
class BaghChal : public QMainWindow
{
    Q_OBJECT

public:
    void showMessage(MessageState messageCase, QString msg);    /**< Shows a Message or a Notification */
    void clearStatusMsg();
    void showTurnArrowAndMessage(int turn);                     /**< Shows the Turn Arrow including a Notification */
    static BaghChal *getInstance();                             /**< Getting the instance of the singleton class */
    ~BaghChal();
    list<BoxWidget *> getBoxes();                               /**< Return a List containing all fields of the playing field */

private:
    static BaghChal *baghchal;                                  /**< Singleton of the BaghChal class */
    explicit BaghChal(QWidget *parent = 0);                     /**< Constructor */
    Ui::BaghChal *ui;                                           /**< UI instance, which includes all existing UI elements */
    HelpWindow hw;
    InfoWindow iw;
    QLabel statusMsg;                                           /**< Includes the Message, which is shown in the Statusbar */
    QTimer *timer;
    Game *game;                                                 /**< Instance of class Game, which is the central class for the game logic */
    list<BoxWidget *> boxes;                                    /**< Contains all fields of the playing field */
    bool askSaveDialog();
    void closeEvent(QCloseEvent *event);
    void setStatusMsg(QString msg);                             /**< Setting the Message of the statusbar */
    void renderGame();                                          /**< Setting up a saved Game, after loading it into the logical layer */

private slots:
    void openNewGame();
    void openLoadGame();
    bool openSaveGame();
    void openQuitGame();
    void openHelpWindow();
    void openInfoWindow();
    void hideTurnNotification();
};

#endif // BAGHCHAL_H
