/**
* AvatarWidget Class
* @file AvatarWidget.h
* @brief Headerfile for AvatarWidget Class
* @see AvatarWidget
* @author Simon Schneeberger
*/

#ifndef AVATARWIDGET_H
#define AVATARWIDGET_H

#include <QWidget>

class QMouseEvent;

/**
* @class AvatarWidget
* @brief Derived Class from QWidget of an avatar in the game
* 
* The AvatarWidget class represents a player avatar goat or tiger
*/
class AvatarWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AvatarWidget(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *event);
    
private:
    void cleanAvatars();
   
signals:

public slots:

};

#endif // AVATARWIDGET_H
