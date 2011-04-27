#ifndef BAGHCHAL_H
#define BAGHCHAL_H

#include <QMainWindow>

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

private slots:
    void openHelpWindow();
    void openInfoWindow();
};

#endif // BAGHCHAL_H
