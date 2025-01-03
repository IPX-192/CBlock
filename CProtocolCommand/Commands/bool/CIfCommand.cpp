#include "CIfCommand.h"
#include "CMessage.h"
#include "CCommandExecuteThread.h"
#include <QColor>
#include <QDebug>

CIfCommand::CIfCommand() {}

CIfCommand::~CIfCommand()
{
    if(m_Condition != nullptr)
    {
        delete m_Condition;
    }
    if(m_Body != nullptr)
    {
        delete m_Body;
    }
}

QList<CCommand::ParamType> CIfCommand::getParamTypes() const
{
    QList<CCommand::ParamType> params;
    params.append(CCommand::BOOLEAN_EXPRESSION);
    return params;
}

void CIfCommand::executeNextStep(CCommandExecuteThread &executionThread) const
{
    //check if block is valid for execution
    if(m_Condition == nullptr || m_Body == nullptr)
    {
        executionThread.endExecution(nullptr);
        return;
    }

    //get message
    IntMessage* m = (IntMessage*)executionThread.getMessage();
    if(m == nullptr)
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
        if(value == nullptr || !value->toBool())
        {
            qDebug()<<u8"if表达式是不成立的";
            executionThread.endExecution(nullptr);
            return;
        }

        qDebug()<<u8"if表达式是成立的";
        //if condition true -> execute body
        executionThread.setNextBlock(m_Body);
        m->setValue(2);
        return;
    }

    //end execution
    executionThread.endExecution(nullptr);
}

bool CIfCommand::addParameter(CCommand *parameter, int index)
{
    if(index != 0 || parameter == nullptr)
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

bool CIfCommand::addBody(CStatementCommand *body, int index)
{
    if(index != 0 || body == nullptr)
    {
        return false;
    }
    m_Body = body;
    return true;
}
