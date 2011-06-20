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
#include "HelpWindow.h"
#include "InfoWindow.h"
#include "QTimer"
#include "../logic/Game.h"
#include <list>
#include "BoxWidget.h"
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
    OnlyStatusBar,              /**< Only a statusbar message */
    OnlyNotification,           /**< Notification with timer */
    NotificationWithTimer,      /**< Notification and statusbar message with timer */
    NotificationWithoutTimer    /**< Notification ans statusbar message without timer */
};

/**
 * @class BaghChal
 * @brief Derived class of QMainWindow for the Mainwindow
 *
 * The BaghChal class represents the GUI of the game as a derived class of QMainWindow including a menuebar, a statusbar and several QWidgets.
 */
class BaghChal : public QMainWindow
{
    Q_OBJECT

public:
    void showMessage(MessageState messageCase, QString msg);    /**< Shows a message or a notification */
    void clearStatusMsg();
    void showTurnArrowAndMessage(int turn);                     /**< Shows the turn arrow including a notification */
    static BaghChal *getInstance();                             /**< Get the instance of the singleton class */
    ~BaghChal();
    list<BoxWidget *> getBoxes();                               /**< Returns a list containing all fields of the playing field */

private:
    static BaghChal *baghchal;                                  /**< Singleton of the BaghChal class */
    explicit BaghChal(QWidget *parent = 0);                     /**< Constructor */
    Ui::BaghChal *ui;                                           /**< UI instance, which includes all existing UI elements */
    HelpWindow hw;
    InfoWindow iw;
    QLabel statusMsg;                                           /**< Includes the message, which is shown in the statusbar */
    QTimer *timer;
    Game *game;                                                 /**< Instance of class Game, which is the central class for the game logic */
    list<BoxWidget *> boxes;                                    /**< Contains all fields of the playing field */
    bool askSaveDialog();
    void closeEvent(QCloseEvent *event);
    void setStatusMsg(QString msg);                             /**< Set the message of the statusbar */
    void renderGame();                                          /**< Setting up a saved game, after loading it into the logical layer */

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
