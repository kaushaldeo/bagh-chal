#ifndef AVATARWIDGET_H
#define AVATARWIDGET_H

#include <QWidget>

class QMouseEvent;


class AvatarWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AvatarWidget(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *event);
    
signals:

public slots:

};

#endif // AVATARWIDGET_H
