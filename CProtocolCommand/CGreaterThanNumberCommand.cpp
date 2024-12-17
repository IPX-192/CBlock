#include "CGreaterThanNumberCommand.h"
#include "CMessage.h"
#include "CCommandExecuteThread.h"
#include "CValue.h"


CGreaterThanNumberCommand::CGreaterThanNumberCommand()
{

}

CGreaterThanNumberCommand::~CGreaterThanNumberCommand()
{
    if(_left != NULL)
        delete _left;
    if(_right != NULL)
        delete _right;
}

QList<CCommand::ParamType> CGreaterThanNumberCommand::getParamTypes() const
{
    QList<CCommand::ParamType> params;
    params.append(CCommand::NUMBER_EXPRESSION);
    params.append(CCommand::NUMBER_EXPRESSION);
    return params;
}

void CGreaterThanNumberCommand::executeNextStep(CCommandExecuteThread &executionThread) const
{
    if(_left == NULL || _right == NULL) {
        executionThread.endExecution(NULL);
        return;
    }

    //get message
    ValueMessage* m = (ValueMessage*)executionThread.getMessage();
    if(m == NULL)
    {
        m = new ValueMessage();
        executionThread.setMessage(m);
    }

    //evaluate left
    if(m->getNumber() == 0)
    {
        executionThread.setNextBlock(_left);
        m->setNumber(1);
        return;
    }

    //evaluate right
    if(m->getNumber() == 1)
    {
        m->setValue(executionThread.getReturnValue()->copy());
        //check left value
        if(m->getValue() == NULL || m->getValue()->getDataType() != CValue::NUMBER)
        {
            executionThread.endExecution(NULL);
            return;
        }
        executionThread.setNextBlock(_right);
        m->setNumber(2);
        return;
    }

    //Compire _left and _right
    if(m->getNumber() == 2)
    {
        CValue* v = executionThread.getReturnValue();
        //check right value
        if(v == NULL || v->getDataType() != CValue::NUMBER)
        {
            executionThread.endExecution(NULL);
            return;
        }

        //create return value
        CValue* s = new BooleanValue(m->getValue()->toDouble() > v->toDouble());
        executionThread.endExecution(s);
        return;
    }

    executionThread.endExecution(NULL);
}

bool CGreaterThanNumberCommand::addParameter(CCommand *parameter, int index)
{
    if(parameter == NULL || (parameter->getReturnType() != CCommand::NUMBER_EXPRESSION && parameter->getReturnType() != CCommand::NUMBER_VAR))
    {
        return false;
    }

    if(index == 0)
    {
        _left = (CExpressionCommand*)parameter;
        return true;
    }

    if(index == 1)
    {
        _right = (CExpressionCommand*)parameter;
        return true;
    }

    return false;
}
