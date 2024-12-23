#include "CConstantCommand.h"
#include "CCommandExecuteThread.h"

CConstantCommand::~CConstantCommand()
{
    if(m_Value != NULL)
    {
        delete m_Value;
    }

}

CCommand::ParamType CConstantCommand::getReturnType() const
{
    if(m_Value == NULL)
    {
        return CCommand::VOID;
    }
    switch(m_Value->getDataType())
    {
    case CValue::BOOLEAN:
        return CCommand::BOOLEAN_EXPRESSION;
    case CValue::NUMBER:
        return CCommand::NUMBER_EXPRESSION;
    case CValue::STRING:
        return CCommand::STRING_EXPRESSION;
    default:
        return CCommand::VOID;
    }
}

void CConstantCommand::executeNextStep(CCommandExecuteThread &executionThread) const
{
    CValue *valCopy = NULL;
    if(m_Value != NULL)
        valCopy = m_Value->copy();

    executionThread.endExecution(valCopy);
}
