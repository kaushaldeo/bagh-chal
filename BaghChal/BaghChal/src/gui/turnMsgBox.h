#ifndef TURNMSGBOX_H
#define TURNMSGBOX_H

#include <QWidget>

class TurnMsgBox : public QWidget
{
    Q_OBJECT
public:
    explicit TurnMsgBox(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *event);

signals:
    void clicked();

public slots:

};

#endif // TURNMSGBOX_H
