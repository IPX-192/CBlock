#include "CStartCommand.h"
#include "CCommandExcuteHandler.h"
#include "CStatementCommand.h"

CStartCommand::CStartCommand() {}

void CStartCommand::sendSignal(const CSignal &signal, CSprite *sprite)
{
    if(sprite == NULL || signal.getType() != CSignal::START)
    {
        return;
    }
    sprite->getExecutionHandler()->addExecutionThread(getStatement(), sprite->getVarTable(), sprite);
}


