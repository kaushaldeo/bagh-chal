#ifndef BOXWIDGET_H
#define BOXWIDGET_H

#include <QWidget>

class QDragEnterEvent;
class QDropEvent;
class QDragMoveEvent;


class BoxWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BoxWidget(QWidget *parent = 0);
    
protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    
signals:

public slots:
	
};

#endif // BOXWIDGET_H
