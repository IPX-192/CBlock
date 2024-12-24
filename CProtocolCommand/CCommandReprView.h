#ifndef CCOMMANDREPRVIEW_H
#define CCOMMANDREPRVIEW_H

#include <QGraphicsItem>
#include <QPainterPath>
#include <QDrag>
#include <QColor>
#include <QGraphicsSceneContextMenuEvent>

#include "CCommandRepr.h"
#include "CCommandReprviewholder.h"

class BlockColors
{
public:
    static QColor getColor(CCommand::ParamType paramType);

private:
    BlockColors() {}
};

class CCommandReprView : public QObject, public QGraphicsItem
{

    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    static CCommandReprView* newBlockReprView(CCommandRepr* blockRepr, QGraphicsItem *parent = 0);

    virtual ~CCommandReprView();

    virtual QRectF boundingRect() const {return _bounds;}

    virtual QPainterPath shape () const {return _shape;}

    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

    CCommandRepr* getBlockRepr() const {return _blockRepr;}


private:
    void init();

    QPoint* createPolygonPoints() const;

    QPolygon createPolygon() const;

    void resetHolders();

    void setCursorPixmap(QDrag* drag, QPoint position);


public slots:
    /**
     * @brief Updates the boundingRect and the position of the child blocks
     */
    virtual void updateBlock();


protected:

    explicit CCommandReprView(CCommandRepr* blockRepr, QGraphicsItem *parent = 0);

    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

    virtual void dragEnterEvent(QGraphicsSceneDragDropEvent* event);
    virtual void dropEvent(QGraphicsSceneDragDropEvent* event);
    virtual void dragLeaveEvent(QGraphicsSceneDragDropEvent* event);

    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent* event);

private:
    CCommandRepr* _blockRepr;
    QGraphicsItem** _params;
    bool* _isParamHolder;
    QGraphicsItem** _bodies;
    bool* _isBodyHolder;
    QGraphicsItem* _nextStatement;
    bool _isNextStatementHolder;
    QPolygon _polygon;
    QRectF _bounds;
    QPainterPath _shape;

};

#endif // CCOMMANDREPRVIEW_H
