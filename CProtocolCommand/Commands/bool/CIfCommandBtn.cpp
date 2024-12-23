#include "CIfCommandBtn.h"
#include "CMessage.h"
#include "CCommandExecuteThread.h"

CIfCommandBtn::CIfCommandBtn() {}

CIfCommandBtn::~CIfCommandBtn()
{
    if(m_Condition != NULL)
        delete m_Condition;
    if(m_Body != NULL)
        delete m_Body;
}

QList<CCommand::ParamType> CIfCommandBtn::getParamTypes() const
{
    QList<CCommand::ParamType> params;
    params.append(CCommand::BOOLEAN_EXPRESSION);
    return params;
}

void CIfCommandBtn::executeNextStep(CCommandExecuteThread &executionThread) const
{
    //check if block is valid for execution
    if(m_Condition == NULL || m_Body == NULL) {
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
        if(value == NULL || !value->toBool())
        {
            qDebug()<<u8"表达式是不成立的";
            executionThread.endExecution(NULL);
            return;
        }

        qDebug()<<u8"表达式是成立的";
        //if condition true -> execute body
        executionThread.setNextBlock(m_Body);
        m->setValue(2);
        return;
    }

    //end execution
    executionThread.endExecution(NULL);
}

bool CIfCommandBtn::addParameter(CCommand *parameter, int index)
{
    if(index != 0 || parameter == NULL)
        return false;

    if(parameter->getReturnType() != CCommand::BOOLEAN_EXPRESSION && parameter->getReturnType() != CCommand::BOOLEAN_VAR)
        return false;

    m_Condition = (CExpressionCommand*)parameter;

    return true;
}

bool CIfCommandBtn::addBody(CStatementCommand *body, int index)
{
    if(index != 0 || body == NULL)
        return false;

    m_Body = body;

    return true;
}
