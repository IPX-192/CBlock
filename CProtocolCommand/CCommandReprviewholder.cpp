#include "CCommandReprviewholder.h"

#include <QPainter>
#include <QGraphicsSceneDragDropEvent>
#include <QDebug>

#include "CCommandRepr.h"
#include "CCommandReprView.h"

BlockReprViewHolder::BlockReprViewHolder(CCommand::ParamType paramType, int index, bool isParam, CCommandReprView *parentBlock) :
    QGraphicsItem(parentBlock), _paramType(paramType), _parentBlock(parentBlock), _index(index), _isParam(isParam)
{
    _brush.setColor(BlockColors::getColor(_paramType).lighter(125));
    _brush.setStyle(Qt::SolidPattern);
    _borderPen = QPen(Qt::black);
    setAcceptDrops(true);
}

BlockReprViewHolder::~BlockReprViewHolder()
{

}

QRectF BlockReprViewHolder::boundingRect() const
{
    return QRectF(QPointF(0, 0), CCommandRepr::HOLDER_SIZE);
}

void BlockReprViewHolder::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    /*painter->setBrush(QBrush(QColor(255, 255, 255)));*/
    painter->setPen(_borderPen);
    /*painter->drawRect(boundingRect());*/
    painter->setBrush(_brush);
    painter->drawRect(boundingRect());
}

bool BlockReprViewHolder::dropBlock(CCommandRepr* block)
{
    return false;
}

void BlockReprViewHolder::dragEnterEvent(QGraphicsSceneDragDropEvent* event)
{

}

void BlockReprViewHolder::dropEvent(QGraphicsSceneDragDropEvent* event)
{

}

void BlockReprViewHolder::dragLeaveEvent(QGraphicsSceneDragDropEvent* event)
{
    QGraphicsItem::dragLeaveEvent(event);

    _brush.setStyle(Qt::SolidPattern);
    _borderPen = QPen(Qt::black);
    update(boundingRect());
}
