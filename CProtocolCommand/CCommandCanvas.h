#ifndef CCOMMANDCANVAS_H
#define CCOMMANDCANVAS_H

#include <QGraphicsScene>
#include <QList>
#include "CCommandReprView.h"
class CProtocolCommand;


class CCommandCanvas : public QGraphicsScene
{
    Q_OBJECT
public:
    CCommandCanvas();

    explicit CCommandCanvas(CProtocolCommand* protocolCommand,QObject *parent = 0);

    ~CCommandCanvas();


    void resetList();

    void buildList();


protected:
    virtual void dragMoveEvent(QGraphicsSceneDragDropEvent* event);
    virtual void dragEnterEvent(QGraphicsSceneDragDropEvent* event);
    virtual void dropEvent(QGraphicsSceneDragDropEvent* event);
    virtual void dragLeaveEvent(QGraphicsSceneDragDropEvent* event);

private:
    QList<CCommandReprView*> _blocks;
    CProtocolCommand* m_pProtocolCommand{nullptr};

};

#endif // CCOMMANDCANVAS_H
