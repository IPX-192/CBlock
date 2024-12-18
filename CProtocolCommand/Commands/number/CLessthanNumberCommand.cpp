#include "CLessThanNumberCommand.h"
#include "CMessage.h"
#include "CCommandExecuteThread.h"
#include "CValue.h"

CLessThanNumberCommand::CLessThanNumberCommand() {}

CLessThanNumberCommand::~CLessThanNumberCommand()
{
    if(m_Left != nullptr)
    {
        delete m_Left;
        m_Left = nullptr;
    }
    if(m_Right != nullptr)
    {
        delete m_Right;
        m_Right = nullptr;
    }
}

QList<CCommand::ParamType> CLessThanNumberCommand::getParamTypes() const
{
    QList<CCommand::ParamType> params;
    params.append(CCommand::NUMBER_EXPRESSION);
    params.append(CCommand::NUMBER_EXPRESSION);
    return params;
}

void CLessThanNumberCommand::executeNextStep(CCommandExecuteThread &executionThread) const
{
    if(m_Left == nullptr || m_Right == nullptr) {
        executionThread.endExecution(nullptr);
        return;
    }

    //get message
    ValueMessage* m = (ValueMessage*)executionThread.getMessage();
    if(m == nullptr)
    {
        m = new ValueMessage();
        executionThread.setMessage(m);
    }

    //evaluate left
    if(m->getNumber() == 0)
    {
        executionThread.setNextBlock(m_Left);
        m->setNumber(1);
        return;
    }

    //evaluate right
    if(m->getNumber() == 1)
    {
        m->setValue(executionThread.getReturnValue()->copy());
        //check left value
        if(m->getValue() == nullptr || m->getValue()->getDataType() != CValue::NUMBER)
        {
            executionThread.endExecution(nullptr);
            return;
        }
        executionThread.setNextBlock(m_Right);
        m->setNumber(2);
        return;
    }

    //Compire m_Left and m_Right
    if(m->getNumber() == 2)
    {
        CValue* v = executionThread.getReturnValue();
        //check right value
        if(v == nullptr || v->getDataType() != CValue::NUMBER)
        {
            executionThread.endExecution(nullptr);
            return;
        }

        //create return value
        CValue* s = new NumberValue(m->getValue()->toDouble() < v->toDouble());
        executionThread.endExecution(s);
        return;
    }

    executionThread.endExecution(nullptr);
}

bool CLessThanNumberCommand::addParameter(CCommand *parameter, int index)
{
    if(parameter == nullptr || (parameter->getReturnType() != CCommand::NUMBER_EXPRESSION && parameter->getReturnType() != CCommand::NUMBER_VAR))
    {
        return false;
    }

    if(index == 0)
    {
        m_Left = (CExpressionCommand*)parameter;
        return true;
    }

    if(index == 1)
    {
        m_Right = (CExpressionCommand*)parameter;
        return true;
    }

    return false;
}
