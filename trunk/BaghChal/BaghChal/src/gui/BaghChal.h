#ifndef BAGHCHAL_H
#define BAGHCHAL_H

#include <QMainWindow>
#include "QCloseEvent"
#include "helpWindow.h"
#include "infoWindow.h"
#include "QTimer"

namespace Ui {
    class BaghChal;
}

class BaghChal : public QMainWindow
{
    Q_OBJECT

public:
    explicit BaghChal(QWidget *parent = 0);
    ~BaghChal();

    void setTurnNotification(int turn);
    void setStatusMsg(QString msg);
    void clearStatusMsg();

private:
    Ui::BaghChal *ui;
    HelpWindow hw;
    InfoWindow iw;
    QLabel statusMsg;
    QTimer *timer;

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
