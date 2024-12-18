#include "CNumberRassignment.h"
#include "CMessage.h"
#include "CCommandExecuteThread.h"
#include "CValue.h"

CNumberRassignment::CNumberRassignment() {}

CNumberRassignment::~CNumberRassignment()
{
    if(m_VarCommand != nullptr)
    {
        delete m_VarCommand;
        m_VarCommand = nullptr;
    }
    if(m_Expression != nullptr)
    {
        delete m_Expression;
        m_Expression = nullptr;
    }
}

QList<CCommand::ParamType> CNumberRassignment::getParamTypes() const
{
    QList<CCommand::ParamType> params;
    params.append(CCommand::NUMBER_EXPRESSION);
    params.append(CCommand::NUMBER_EXPRESSION);
    return params;
}

void CNumberRassignment::executeNextStep(CCommandExecuteThread &executionThread) const
{
    if(m_VarCommand == nullptr || m_Expression == nullptr) {
        executionThread.endExecution(nullptr);
        return;
    }

    //get message
    IntMessage* m = (IntMessage*)executionThread.getMessage();
    if(m == nullptr)
    {
        m = new IntMessage();
        executionThread.setMessage(m);
    }

    if(m->getValue() == 0)
    {
        executionThread.setNextBlock(m_Expression);
        m->setValue(1);
        return;
    }

    if(m->getValue() == 1)
    {

    }

    executionThread.endExecution(nullptr);
}

bool CNumberRassignment::addParameter(CCommand *parameter, int index)
{
    if(parameter == nullptr)
    {
        return false;
    }

    if(index == 0 && parameter->getReturnType() == CCommand::NUMBER_VAR) {
        m_VarCommand = (CVarCommand*)parameter;
        return true;
    }

    if(index == 1 && (parameter->getReturnType() == CCommand::NUMBER_EXPRESSION || parameter->getReturnType() == CCommand::NUMBER_VAR))
    {
        m_Expression = (CExpressionCommand*)parameter;
        return true;
    }

    return false;
}
