#ifndef HELPWINDOW_H
#define HELPWINDOW_H

#include "../../ui_helpWindow.h"

#include <QWidget>

class HelpWindow : public QWidget, public Ui::helpPopup
{
    Q_OBJECT

public:
    explicit HelpWindow(QWidget *parent = 0);
    ~HelpWindow();

};

#endif // HELPWINDOW_H
