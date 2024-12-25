#include "CCommandCanvas.h"
#include "CProtocolCommand.h"
#include <QGraphicsSceneDragDropEvent>
#include <QDebug>

CCommandCanvas::CCommandCanvas(CProtocolCommand *protocolCommand, QObject *parent)
    :QGraphicsScene(parent), m_pProtocolCommand(protocolCommand)
{
    buildList();
}

CCommandCanvas::~CCommandCanvas()
{
    resetList();
}

void CCommandCanvas::resetList()
{
    foreach (CCommandReprView* block, _blocks) {
        if(block->scene() != NULL)
            block->scene()->removeItem(block);
        delete block;
    }
    clear();
    //qDeleteAll(_blocks);
    _blocks.clear();
}

void CCommandCanvas::buildList()
{
    resetList();

    foreach(CCommandRepr* block, m_pProtocolCommand->getBlocks()) {

        CCommandReprView* blockView = CCommandReprView::newBlockReprView(block);
        _blocks.append(blockView);
        blockView->setPos(block->getPosition());
        addItem((QGraphicsItem*)blockView);
    }
}

void CCommandCanvas::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    QGraphicsScene::dragMoveEvent(event);
    event->accept();
    event->setDropAction(Qt::MoveAction);
}

void CCommandCanvas::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    QGraphicsScene::dragEnterEvent(event);
    event->accept();
}

void CCommandCanvas::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    QGraphicsScene::dropEvent(event);

    const BlockMimeData* mime = qobject_cast<const BlockMimeData *>(event->mimeData());
    //check if cast successful
    if (mime) {
        //ignore if drop already successful
        if(mime->getDragInfo()->getDropSuccessful())
            return;

        //get position of drop
        QPoint position = event->scenePos().toPoint() - mime->getDragInfo()->getTopLeft();

        mime->getDragInfo()->getBlockRepr()->setPosition(position);
        mime->getDragInfo()->getBlockRepr()->setHolderParent(m_pProtocolCommand);
        m_pProtocolCommand->addCommand(mime->getDragInfo()->getBlockRepr());

        mime->getDragInfo()->setDropSuccessful(true);
        mime->getDragInfo()->setKeepOriginal(false);
    }
}

void CCommandCanvas::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    QGraphicsScene::dragLeaveEvent(event);
}
