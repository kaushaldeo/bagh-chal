#ifndef BOXWIDGET_H
#define BOXWIDGET_H

#include <QWidget>
#include "../logic/Cell.h"
#include "avatarWidget.h"

class QDragEnterEvent;
class QDropEvent;
class QDragMoveEvent;
class QDragLeaveEvent;

class BoxWidget : public QWidget
{    
    Q_OBJECT

public:
    explicit BoxWidget(QWidget *parent = 0);
    Cell* getCell();
    void setCell(Cell *cell);
    void placeAvatar();
    void placeGoatInRippedField(int eatenGoats);
    
protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);

private:
    bool handleGameAction(AvatarWidget* avatar);
    Cell* cell;
signals:

public slots:
	
};

#endif // BOXWIDGET_H
