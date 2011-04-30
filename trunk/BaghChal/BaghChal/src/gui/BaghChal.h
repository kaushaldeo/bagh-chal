#ifndef BAGHCHAL_H
#define BAGHCHAL_H

#include <QMainWindow>
#include "QWidget"
#include "QCloseEvent"
#include "helpWindow.h"
#include "infoWindow.h"

namespace Ui {
    class BaghChal;
}

class BaghChal : public QMainWindow
{
    Q_OBJECT

public:
    explicit BaghChal(QWidget *parent = 0);
    ~BaghChal();

private:
    Ui::BaghChal *ui;
    HelpWindow hw;
    InfoWindow iw;

    QLabel statusMsg;
    QLabel *turnMsg;
    QWidget *turnNotification;

    bool askSaveDialog();
    void closeEvent(QCloseEvent *event);

    void setStatusMsg(QString msg);
    void clearStatusMsg();
    void setupTurnNotification();
    void setTurnNotification(int turn);

private slots:
    void openLoadGame();
    bool openSaveGame();
    void openQuitGame();
    void openHelpWindow();
    void openInfoWindow();
};

#endif // BAGHCHAL_H
