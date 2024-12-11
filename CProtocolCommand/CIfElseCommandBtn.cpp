#include "CIfElseCommandBtn.h"

CIfElseCommandBtn::CIfElseCommandBtn() {}

CIfElseCommandBtn::~CIfElseCommandBtn()
{
    if(_condition != NULL)
        delete _condition;
    if(_ifBody != NULL)
        delete _ifBody;
    if(_elseBody != NULL)
        delete _elseBody;
}

void CIfElseCommandBtn::executeNextStep(CCommandExecuteThread &executionThread) const
{
    //check if block is valid for execution
    if(_condition == NULL || _ifBody == NULL || _elseBody == NULL) {
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
        executionThread.setNextBlock(_condition);
        m->setValue(1);
        return;
    }

    //check condition and run body if condition evaluated true
    if(m->getValue() == 1)
    {
        Value* value = (Value*) executionThread.getReturnValue();
        //if no return value or false -> end execution
        if(value == NULL)
        {
            executionThread.endExecution(NULL);
            return;
        }
        else if (value->toBool())
        {
            //if condition true -> execute if body
            executionThread.setNextBlock(_ifBody);
            m->setValue(2);
        }
        else if (!value->toBool())
        {
            //if condition false -> execute else body
            executionThread.setNextBlock(_elseBody);
            m->setValue(2);
        }

        return;
    }

    //end execution
    executionThread.endExecution(NULL);
}

bool CIfElseCommandBtn::addParameter(CCommand *parameter, int index)
{
    if(index != 0 || parameter == NULL)
        return false;

    if(parameter->getReturnType() != CCommand::BOOLEAN_EXPRESSION && parameter->getReturnType() != CCommand::BOOLEAN_VAR)
        return false;

    m_Condition = (CExpressionCommand*)parameter;

    return true;
}

bool CIfElseCommandBtn::addBody(CStatementCommand *body, int index)
{
    if(index < 0 || index > 1 || body == NULL)
        return false;

    if (index == 0)
        _ifBody = body;
    else if (index == 1)
        _elseBody = body;

    return true;
}
