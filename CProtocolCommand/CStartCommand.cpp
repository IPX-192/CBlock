#include "CStartCommand.h"

CStartCommand::CStartCommand() {}

void CStartCommand::sendSignal(const CSignal &signal, CObject *sprite)
{
    if(sprite == NULL || signal.getType() != CSignal::START)
    {
        return;
    }
    //  sprite->getExecutionHandler()->addExecutionThread(getStatement(),sprite);
}


