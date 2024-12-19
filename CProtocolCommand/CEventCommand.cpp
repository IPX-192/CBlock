#include "CEventCommand.h"
#include "CStatementCommand.h"

CEventCommand::CEventCommand() {}

CEventCommand::~CEventCommand()
{
    if(m_Statement != nullptr)
    {
        delete m_Statement;
        m_Statement = nullptr;
    }
}
