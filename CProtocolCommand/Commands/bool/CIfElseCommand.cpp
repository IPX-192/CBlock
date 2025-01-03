#include "CIfElseCommand.h"
#include "CMessage.h"
#include "CCommandExecuteThread.h"

CIfElseCommand::CIfElseCommand() {}

CIfElseCommand::~CIfElseCommand()
{
    if(m_Condition != NULL)
        delete m_Condition;
    if(m_IfBody != NULL)
        delete m_IfBody;
    if(m_ElseBody != NULL)
        delete m_ElseBody;
}

QList<CCommand::ParamType> CIfElseCommand::getParamTypes() const
{
    QList<CCommand::ParamType> params;
    params.append(CCommand::BOOLEAN_EXPRESSION);
    return params;
}

void CIfElseCommand::executeNextStep(CCommandExecuteThread &executionThread) const
{
    //check if block is valid for execution
    if(m_Condition == NULL || m_IfBody == NULL || m_ElseBody == NULL) {
        executionThread.endExecution(NULL);
        return;
    }

    //get message
    IntMessage* m = (IntMessage*)executionThread.getMessage();
    if(m == NULL)
    {
        m = new IntMessage(0);
        executionThread.setMessage(m);
    }

    //test condition
    if(m->getValue() == 0)
    {
        executionThread.setNextBlock(m_Condition);
        m->setValue(1);
        return;
    }

    //check condition and run body if condition evaluated true
    if(m->getValue() == 1)
    {
        CValue* value = (CValue*) executionThread.getReturnValue();
        //if no return value or false -> end execution
        if(value == NULL)
        {
            executionThread.endExecution(NULL);
            return;
        }
        else if (value->toBool())
        {
            //if condition true -> execute if body
            executionThread.setNextBlock(m_IfBody);
            m->setValue(2);
        }
        else if (!value->toBool())
        {
            //if condition false -> execute else body
            executionThread.setNextBlock(m_ElseBody);
            m->setValue(2);
        }

        return;
    }

    //end execution
    executionThread.endExecution(NULL);
}

bool CIfElseCommand::addParameter(CCommand *parameter, int index)
{
    if(index != 0 || parameter == NULL)
        return false;

    if(parameter->getReturnType() != CCommand::BOOLEAN_EXPRESSION && parameter->getReturnType() != CCommand::BOOLEAN_VAR)
        return false;

    m_Condition = (CExpressionCommand*)parameter;

    return true;
}

bool CIfElseCommand::addBody(CStatementCommand *body, int index)
{
    if(index < 0 || index > 1 || body == NULL)
        return false;

    if (index == 0)
        m_IfBody = body;
    else if (index == 1)
        m_ElseBody = body;

    return true;
}
