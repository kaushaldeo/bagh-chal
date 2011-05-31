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



namespace Ui {
    class BaghChal;
}

enum MessageState
{ 
    OnlyStatusBar,
    OnlyNotification,
    NotificationWithTimer,
    NotificationWithoutTimer
};

class BaghChal : public QMainWindow
{
    Q_OBJECT

public:
    void showMessage(int caseNumber, QString msg);
    void clearStatusMsg();
    void showTurnArrowAndMessage(int turn);
    static BaghChal* getInstance();
    ~BaghChal();

private:
    static BaghChal* baghchal;
    explicit BaghChal(QWidget *parent = 0);
    Ui::BaghChal *ui;
    HelpWindow hw;
    InfoWindow iw;
    QLabel statusMsg;
    QTimer *timer;
    Game* game;
    list<BoxWidget*> boxes;
    bool askSaveDialog();
    void closeEvent(QCloseEvent *event);
    void setStatusMsg(QString msg);
    void renderGame();
    
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
