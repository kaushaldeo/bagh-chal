#ifndef BAGHCHAL_H
#define BAGHCHAL_H

#include <QMainWindow>
#include "QCloseEvent"
#include "helpWindow.h"
#include "infoWindow.h"
#include "QTimer"
#include "../logic/Game.h"
#include <set>
#include "boxWidget.h"

namespace Ui {
    class BaghChal;
}

class BaghChal : public QMainWindow
{
    Q_OBJECT

public:
    void setTurnNotification(int turn);
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
    set<BoxWidget*> boxes;
    bool askSaveDialog();
    void closeEvent(QCloseEvent *event);
    void setStatusMsg(QString msg);
    bool renderGame();
    
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
