#ifndef BAGHCHAL_H
#define BAGHCHAL_H

#include <QMainWindow>
#include "QCloseEvent"
#include "helpWindow.h"
#include "infoWindow.h"
#include "QTimer"
#include "../logic/Game.h"

namespace Ui {
    class BaghChal;
}

class BaghChal : public QMainWindow
{
    Q_OBJECT

public:
    void setTurnNotification(int turn);
    void setStatusMsg(QString msg);
    void clearStatusMsg();
    void showTurnArrow(int turn);
    Game* getGame();
    //static BaghChal* getInstance();
        explicit BaghChal(QWidget *parent = 0);

    ~BaghChal();

private:
    //static BaghChal* baghchal;
    Ui::BaghChal *ui;
    HelpWindow hw;
    InfoWindow iw;
    QLabel statusMsg;
    QTimer *timer;
    Game* game;
    bool askSaveDialog();
    void closeEvent(QCloseEvent *event);

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
