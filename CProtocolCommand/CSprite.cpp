#include "CSprite.h"
#include "CCommandExcuteHandler.h"




CSprite::CSprite(SimpleVarTable *globalVars)
{

}

CSprite::~CSprite()
{

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
