#include "CSprite.h"
#include "CCommandExcuteHandler.h"
#include <QDebug>



CSprite::CSprite(SimpleVarTable *globalVars)
{
    m_SpriteVars = new SpriteVarTable(globalVars);
}

CSprite::~CSprite()
{
    qDeleteAll(m_qlistEventCommand);

    delete m_SpriteVars;
}

void CSprite::setExecutionHandler(CCommandExcuteHandler *test)
{
    m_pExcuteHandler = test;
}

CCommandExcuteHandler *CSprite::getExecutionHandler()
{
    if(m_pExcuteHandler!= nullptr)
    {
        return m_pExcuteHandler;
    }

    return nullptr;
}

void CSprite::sendSignal(const CSignal &signal)
{
    foreach (CEventCommand* b, m_qlistEventCommand) {
        qDebug()<<"sfafasfasfasfafa "<<b->getId();
        b->sendSignal(signal, this);
    }
}
