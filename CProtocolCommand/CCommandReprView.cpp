#include "CCommandReprView.h"
#include <QCursor>
#include <QPainter>
#include <QPixmap>
#include <QGraphicsScene>
#include <QCursor>
#include <QDrag>
#include <QGraphicsView>
#include <QApplication>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneDragDropEvent>
#include <QMenu>
#include <QDebug>

#include "CCommand.h"
#include "CNumberConstantCommandBtnView.h"


CCommandReprView *CCommandReprView::newBlockReprView(CCommandRepr *blockRepr, QGraphicsItem *parent)
{
    //test if blockRepr is ConstantBlock
    if(blockRepr->isConstantBlockRepr())
    {
        if(blockRepr->getReturnType() == CCommand::STRING_EXPRESSION)
        {
        }
        if(blockRepr->getReturnType() == CCommand::NUMBER_EXPRESSION)
        {
            return new CNumberConstantCommandBtnView((CConstantCommandBtn*)blockRepr, parent);
        }
    }

    //return base class implementation
    return new CCommandReprView(blockRepr, parent);
}

CCommandReprView::CCommandReprView(CCommandRepr* blockRepr, QGraphicsItem *parent) : QGraphicsItem(parent), _blockRepr(blockRepr), _nextStatement(NULL)
{

    //设置鼠标光标变成手掌
    //setCursor(QCursor(Qt::OpenHandCursor));

    init();

    resetHolders();

    updateBlock();
}


CCommandReprView::~CCommandReprView()
{
    delete [] _params;
    delete [] _bodies;

    delete [] _isParamHolder;
    delete [] _isBodyHolder;
}

void CCommandReprView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //draw polygon
    painter->setBrush(QBrush(BlockColors::getColor(_blockRepr->getReturnType())));
    painter->setPen(QPen(QBrush(BlockColors::getColor(_blockRepr->getReturnType()).darker(200)), 1));
    painter->drawPolygon(_polygon);

    //draw descriptions
    painter->setPen(Qt::black);
    painter->setFont(CCommandRepr::FONT);

    for(int i = 0; i < _blockRepr->getParamDescriptions().size(); i++)
    {
        painter->drawText(_blockRepr->getParamDescriptionPosition(i), _blockRepr->getParamDescriptions().at(i));
    }
    for(int i = 0; i < _blockRepr->getBodyDescriptions().size(); i++)
    {
        painter->drawText(_blockRepr->getBodyDescriptionPosition(i), _blockRepr->getBodyDescriptions().at(i));
    }

}

void CCommandReprView::init()
{
    //set holder in each param
    _params = new QGraphicsItem*[_blockRepr->getNumParams()];
    _isParamHolder = new bool[_blockRepr->getNumParams()];
    for(int i = 0; i < _blockRepr->getNumParams(); i++) {
        _params[i] = new BlockReprViewHolder(_blockRepr->getParamType(i), i, true, this);
        _isParamHolder[i] = true;
    }

    //set holder in each body
    _bodies = new QGraphicsItem*[_blockRepr->getNumBodies()];
    _isBodyHolder = new bool[_blockRepr->getNumBodies()];
    for(int i = 0; i < _blockRepr->getNumBodies(); i++) {
        _bodies[i] = new BlockReprViewHolder(CCommand::VOID, i, false, this);
        _isBodyHolder[i] = true;
    }

    //set holder on nextStatement
    if(_blockRepr->getReturnType() == CCommand::VOID || _blockRepr->getReturnType() == CCommand::EVENT || _blockRepr->getReturnType() == CCommand::FUNCTION_START) {
        // _nextStatement = new BlockReprViewHolder(CCommand::VOID, -1, false, this);
        _isNextStatementHolder = true;
    }

    setAcceptDrops(true);

    connect(_blockRepr, SIGNAL(blockUpdated()), this, SLOT(updateBlock()));
}

QPoint *CCommandReprView::createPolygonPoints() const
{

    int numBodies = _blockRepr->getNumBodies();

    //total points = numBodies * 4
    int numPoints = numBodies*4+4;
    QPoint* points = new QPoint[numPoints];

    //top left
    points[0].setX(0);
    points[0].setY(0);

    //top right
    int margin = (_blockRepr->getReturnType() == CCommand::VOID || _blockRepr->getReturnType() == CCommand::EVENT) ? CCommandRepr::LEFT_GUTTER : 0;
    points[1].setX(_blockRepr->getHeaderSize().width() + margin);
    points[1].setY(0);

    //right
    points[2].setX(points[1].x());
    points[2].setY(_blockRepr->getHeaderSize().height());

    for(int i = 0; i < numBodies; i++)
    {
        //top left
        points[(i*4)+3].setX(_blockRepr->LEFT_GUTTER);
        points[(i*4)+3].setY(points[(i*4)+2].y());

        //down
        points[(i*4)+4].setX(_blockRepr->LEFT_GUTTER);
        points[(i*4)+4].setY(points[(i*4)+3].y() + _blockRepr->getBodySize(i).height());

        //if next body following
        if((i*4)+1 < numBodies)
        {
            //right
            points[(i*4)+5].setX(_blockRepr->LEFT_GUTTER + _blockRepr->getBodyDescriptionSize(i+1).width());
            points[(i*4)+5].setY(points[(i*4)+4].y());

            //down
            points[(i*4)+6].setX(points[(i*4)+5].x());
            points[(i*4)+6].setY(points[(i*4)+5].y() + _blockRepr->getBodyDescriptionSize(i+1).height());
        }

        //bottom part
        else
        {
            //right
            points[(i*4)+5].setX(_blockRepr->LEFT_GUTTER + _blockRepr->FOOTER_WIDTH);
            points[(i*4)+5].setY(points[(i*4)+4].y());

            //down
            points[(i*4)+6].setX(points[(i*4)+5].x());
            points[(i*4)+6].setY(points[(i*4)+5].y() + _blockRepr->FOOTER_HEIGHT);
        }
    }

    //bottom left
    points[numPoints-1].setX(0);
    points[numPoints-1].setY(points[numPoints-2].y());

    return points;
}

QPolygon CCommandReprView::createPolygon() const
{
    QPolygon p;
    QPoint* points = createPolygonPoints();
    int numPoints = _blockRepr->getNumBodies()*4+4;
    for(int i = 0; i < numPoints; i++)
        p.append(points[i]);
    delete [] points;

    return p;
}

void CCommandReprView::resetHolders()
{
    //reset params
    for(int i = 0; i < _blockRepr->getNumParams(); i++) {
        //change holder to block
        if(_blockRepr->getParam(i) != NULL && _isParamHolder[i]) {
            delete _params[i];
            _params[i] = newBlockReprView(_blockRepr->getParam(i), this);
            _isParamHolder[i] = false;
        }
        //change block to holder
        else if(_blockRepr->getParam(i) == NULL && !_isParamHolder[i]) {
            delete _params[i];
            _params[i] = new BlockReprViewHolder(_blockRepr->getParamType(i), i, true, this);
            _isParamHolder[i] = true;
        }
    }

    //reset bodies
    for(int i = 0; i < _blockRepr->getNumBodies(); i++) {
        if(_blockRepr->getBody(i) != NULL && _isBodyHolder[i]) {
            delete _bodies[i];
            _bodies[i] = newBlockReprView(_blockRepr->getBody(i), this);
            _isBodyHolder[i] = false;
        }
        else if(_blockRepr->getBody(i) == NULL && !_isBodyHolder[i]) {
            delete _bodies[i];
            _bodies[i] = new BlockReprViewHolder(CCommand::VOID, i, false, this);
            _isBodyHolder[i] = true;
        }
    }

    //reset nextStatement
    if(_blockRepr->getReturnType() == CCommand::VOID || _blockRepr->getReturnType() == CCommand::EVENT || _blockRepr->getReturnType() == CCommand::FUNCTION_START) {
        if(_blockRepr->getNextStatement() != NULL && _isNextStatementHolder) {
            delete _nextStatement;
            _nextStatement = newBlockReprView(_blockRepr->getNextStatement(), this);
            _isNextStatementHolder = false;
        }
        else if(_blockRepr->getNextStatement() == NULL && !_isNextStatementHolder) {
            delete _nextStatement;
            _nextStatement = new BlockReprViewHolder(CCommand::VOID, -1, false, this);
            _isNextStatementHolder = true;
        }
    }
}

void CCommandReprView::setCursorPixmap(QDrag *drag, QPoint position)
{

}

void CCommandReprView::updateBlock()
{
    prepareGeometryChange();

    resetHolders();

    //boundingRect
    _bounds = QRectF(QPointF(0, 0), _blockRepr->getTotalSize());

    //params
    for(int i = 0; i < _blockRepr->getNumParams(); i++)
    {
        _params[i]->setPos(_blockRepr->getParamPosition(i));
    }

    //bodies
    for(int i = 0; i < _blockRepr->getNumBodies(); i++)
    {
        _bodies[i]->setPos(_blockRepr->getBodyPosition(i));
    }

    //nextStatement
    if(_nextStatement != NULL)
    {
        _nextStatement->setPos(_blockRepr->getNextStatementPosition());
    }

    _polygon = createPolygon();
    _shape = QPainterPath();
    _shape.addPolygon(_polygon);
}

void CCommandReprView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<u8"鼠标按下物块" << event->pos();

    if (event->button() != Qt::LeftButton) {
        event->ignore();
        return;
    }
    setCursor(QCursor(Qt::ClosedHandCursor));
}

void CCommandReprView::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<u8"鼠标移动物块";


    bool isLocked = _blockRepr->isLocked();

    // Create a drag object with mimetype data.
    QDrag* drag = new QDrag(event->widget());
    BlockMimeData* mime = new BlockMimeData();
    drag->setMimeData(mime);
    mime->getDragInfo()->setTopLeft(event->pos().toPoint());

    //remove block from scene if blockrepr is not locked
    if(!isLocked)
    {
        qDebug()<<"vsdsadasfsafafafa1 ";
        scene()->removeItem(this);
    }

    //set drag pixmap
    setCursorPixmap(drag, event->pos().toPoint());

    //add (copy of) this block to the drag
    if(isLocked) {
        qDebug()<<"vsdsadasfsafafafa2 ";
        mime->getDragInfo()->setBlockRepr(_blockRepr->copy());
        mime->getDragInfo()->getBlockRepr()->setLock(false);
    }
    else {
        mime->getDragInfo()->setBlockRepr(_blockRepr);
        //remove BlockRepr from its parent
        _blockRepr->removeFromParent();
    }

    //Start the drag operation.
    drag->exec();

    //check if drop was successful
    if(!mime->getDragInfo()->getDropSuccessful()) {

        if(isLocked)
        {
            //拖了没拖走
            delete mime->getDragInfo()->getBlockRepr();
        }

        else
        {
            qDebug()<<"vsdsadasfsafafafa4 ";
           mime->getDragInfo()->getBlockRepr()->revert();
        }

    }
}

void CCommandReprView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setCursor(QCursor(Qt::OpenHandCursor));
}

void CCommandReprView::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    QGraphicsItem::dragEnterEvent(event);
}

void CCommandReprView::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    QGraphicsItem::dropEvent(event);
}

void CCommandReprView::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    QGraphicsItem::dragLeaveEvent(event);
}

void CCommandReprView::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{

}

QColor BlockColors::getColor(CCommand::ParamType paramType)
{
    if(paramType == CCommand::VOID)
        return QColor(220, 220, 0);

    if(paramType == CCommand::BOOLEAN_EXPRESSION)
        return QColor(0, 230, 0);

    if(paramType == CCommand::BOOLEAN_VAR)
        return QColor(0, 200, 0);

    if(paramType == CCommand::BOOLEAN_LIST)
        return QColor(0, 170, 0);


    if(paramType == CCommand::NUMBER_EXPRESSION)
        return QColor(0, 200, 240);

    if(paramType == CCommand::NUMBER_VAR)
        return QColor(0, 170, 210);

    if(paramType == CCommand::NUMBER_LIST)
        return QColor(0, 140, 190);


    if(paramType == CCommand::STRING_EXPRESSION)
        return QColor(250, 80, 35);

    if(paramType == CCommand::STRING_VAR)
        return QColor(220, 70, 25);

    if(paramType == CCommand::STRING_LIST)
        return QColor(200, 65, 20);


    if(paramType == CCommand::EVENT)
        return QColor(220, 190, 10);

    if(paramType == CCommand::SPRITE)
        return QColor(170, 110, 70);

    return QColor(100, 100, 100);
}
