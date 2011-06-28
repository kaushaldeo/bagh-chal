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
#include <QCloseEvent>
#include <QDebug>
#include <QTimer>

#include "BoxWidget.h"
#include "HelpWindow.h"
#include "InfoWindow.h"
#include "../logic/Game.h"
#include <list>

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
 * @brief Subclass of QMainWindow
 *
 * The BaghChal class represents the GUI of the game as a subclass of QMainWindow including a menuebar, a statusbar and several QWidgets.
 */
class BaghChal : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @fn showMessage(MessageState messageCase, QString msg)
     * @brief Shows a Message Notification
     * @param messageCase - The case, if message is a notification, a statusbar message or both of them
     * @param msg - Content of the message as a string
     *
     * Shows a message as a notification or as a statusbar message or both of them with and without timer.
     */
    void showMessage(MessageState messageCase, QString msg);
    
    /**
     * @fn clearStatusMsg()
     * @brief Clears the status message
     *
     * This function clears the content of the statusbar.
     */
    void clearStatusMsg();
    
    /**
     * @fn showTurnArrowAndMessage(int turn)
     * @brief Shows, whose turn is it.
     * @param turn - int value containing, whose turn is it
     * @see showMessage
     *
     * Shows the arrow and the statusbar message, which notifies whose turn is it.
     */
    void showTurnArrowAndMessage(int turn); 
    
    /**
     * @fn *getInstance()
     * @brief Returns the singleton baghchal
     *
     * Creates a singleton, if it doesn't already exist, and returns the singleton.
     */
    static BaghChal *getInstance();
    
    /**
     * @fn ~BaghChal()
     * @brief Destructor
     * 
     * Deletes timer, ui and baghchal, and sets singleton baghchal to NULL
     */    
    ~BaghChal();
    
    /**
     * @fn getBoxes()
     * @brief Returns a list containing all objects of the Boxwidget class
     * @return list<BoxWidget *> 
     *
     * Returns a list containing all objects of the BoxWidget class.
     */
    list<BoxWidget *> getBoxes();                             

private:
    static BaghChal *baghchal;  /**< Singleton of the BaghChal class */
    
    /**
     * @fn BaghChal(QWidget *parent = 0)
     * @brief Constructor
     * @param parent - The parent QWidget element
     *
     * This function sets up the UI and creates an instance of the class Game. It also connects all menue items to their corresponding slots.
     * Every object of the BoxWidget class are added to a list.
     */   
    explicit BaghChal(QWidget *parent = 0); 
    
    Ui::BaghChal *ui;            /**< UI instance, which includes all existing UI elements */                                       
    HelpWindow hw;
    InfoWindow iw;
    QLabel statusMsg;            /**< Includes the message, which is shown in the statusbar */                                        
    QTimer *timer;
    Game *game;                  /**< Instance of class Game, which is the central class for the game logic */                                
    list<BoxWidget *> boxes;     /**< Contains all fields of the playing field */
    
    /**
     * @fn askSaveDialog()
     * @brief Opens the save game dialogue
     * @see openSaveGame()
     * @return bool
     *
     * Opens the save game dialogue and returns if the game was saved/discarded or cancled. Calls openSaveGame() if the user wants to save.
     */    
    bool askSaveDialog();
    
    /**
     * @fn closeEvent(QCloseEvent *event)
     * @brief The close event from Qt
     * @param event - QCloseEvent value
     * @see openQuitGame()
     *
     * This function is called, when the user clicks on the close button of the window (the 'X' button).
     * This function simply ignores the QCloseEvent and calls the openQuitGame() function to avoid closing the game without showing the save game dialogue.
     */
    void closeEvent(QCloseEvent *event);
    
    /**
     * @fn setStatusMsg(QString msg)
     * @brief Sets the message of the statusbar
     * @param msg - The message for the statusbar
     *
     * This function sets the statusbar message to the string which is passed by the parameter.
     */
    void setStatusMsg(QString msg);
    
    /**
     * @fn renderGame()
     * @brief Sets up a saved Game
     * @see BoxWidget::placeGoatInRippedField()
     * @see showTurnArrowAndMessage()
     *
     * Setting up a saved game, after loading it into the logical layer. After resetting the current game, all the avatars are placed on their correct position in the playing field.
     */    
    void renderGame();                                         

private slots:
    /**
     * @fn openNewGame()
     * @brief Opens a new game
     * @see askSaveDialog()
     *
     * If the current game was changed the save game dialogue opens. If the game was successfully saved or discarded, the function creates a new game.
     */
    void openNewGame();
    
    /**
     * @fn openLoadGame()
     * @brief Opens the Load Game Dialogue
     * @see FileIO::loadGame()
     * @see renderGame()
     *
     * Opens the load game dialogue and calls the function loadGame() to load a saved game into the logical layer. After loading the game it calls the renderGame() function to set up the game.
     */
    void openLoadGame();
    
    /**
     * @fn openSaveGame()
     * @brief Opens the save game dialogue
     * @see saveGame()
     * @return bool
     *
     * Opens the save game dialogue and calls the function saveGame() to create a save game file. Return if the game was successfully saved or not.
     */
    bool openSaveGame();
    
    /**
     * @fn openQuitGame()
     * @brief Quits the Game
     * @see askSaveDialog()
     *
     * Calls the askSaveDialog() function to ask if the game should be saved before it quits the game.
     */
    void openQuitGame();
    
    /**
     * @fn openHelpWindow()
     * @brief Opens the Help Window
     *
     * This function opens the help window.
     */
    void openHelpWindow();
    
    /**
     * @fn openInfoWindow()
     * @brief Opens the Info Window
     *
     * This funktion opens the info window.
     */
    void openInfoWindow();
    
    /**
     * @fn hideTurnNotification()
     * @brief Makes the turn notification disappear
     *
     * If the game did not end, the turn notification can disappear. Otherwise, if the game did end, it is not possible to let the turn notification disappear.
     */
    void hideTurnNotification();
};

#endif // BAGHCHAL_H
