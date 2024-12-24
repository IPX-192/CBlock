#ifndef BLOCKREPRVIEWHOLDER_H
#define BLOCKREPRVIEWHOLDER_H

#include <QGraphicsItem>
#include <QPen>

#include "CCommand.h"

class CCommandRepr;
class CCommandReprView;

class BlockReprViewHolder : public QGraphicsItem
{
public:

    BlockReprViewHolder(CCommand::ParamType paramType, int index, bool isParam, CCommandReprView* parentBlock);

    ~BlockReprViewHolder();

    QRectF boundingRect() const;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

    int getIndex() const {return _index;}

    bool isParam() const {return _isParam;}

    CCommandReprView* getParentBlock() const {return _parentBlock;}

    bool dropBlock(CCommandRepr *block);

protected:
    virtual void dragEnterEvent(QGraphicsSceneDragDropEvent* event);
    virtual void dropEvent(QGraphicsSceneDragDropEvent* event);
    virtual void dragLeaveEvent(QGraphicsSceneDragDropEvent* event);

private:
    CCommand::ParamType _paramType;
    QBrush _brush;
    QPen _borderPen;

    CCommandReprView* _parentBlock;
    int _index;
    bool _isParam;
};

#endif // BLOCKREPRVIEWHOLDER_H
