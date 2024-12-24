#include "CWhileCommandBtn.h"
#include "CMessage.h"
#include "CCommandExecuteThread.h"


CWhileCommandBtn::~CWhileCommandBtn()
{
    if(m_Condition != nullptr)
    {
        delete m_Condition;
        m_Condition = nullptr;
    }
    if(m_Body != nullptr)
    {
        delete m_Body;
        m_Body = nullptr;
    }
}

QList<CCommand::ParamType> CWhileCommandBtn::getParamTypes() const
{
    QList<CCommand::ParamType> params;
    params.append(CCommand::BOOLEAN_EXPRESSION);
    return params;
}

void CWhileCommandBtn::executeNextStep(CCommandExecuteThread &executionThread) const
{
    //check if block is valid for execution
    if(m_Condition == NULL || m_Body == NULL)
        executionThread.endExecution(NULL);

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
        //重要：while循环只需要判断这个条件是否为真
        if(value == NULL || !value->toBool())
        {


            //qDebug()<<u8"while表达式是不成立的";
            executionThread.endExecution(NULL);
            return;
        }

        //if condition true -> execute body
        executionThread.setNextBlock(m_Body);
        m->setValue(0);
        return;
    }

    //end execution
    executionThread.endExecution(NULL);
}

bool CWhileCommandBtn::addParameter(CCommand *parameter, int index)
{
    if(index != 0 || parameter == NULL)
    {
        return false;
    }

    if(parameter->getReturnType() != CCommand::BOOLEAN_EXPRESSION && parameter->getReturnType() != CCommand::BOOLEAN_VAR)
    {
        return false;
    }

    m_Condition = (CExpressionCommand*)parameter;

    return true;
}

bool CWhileCommandBtn::addBody(CStatementCommand *body, int index)
{
    if(index != 0 || body == NULL)
        return false;

    m_Body = body;

    return true;
}


