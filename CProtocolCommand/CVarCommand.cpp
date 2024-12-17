#include "CVarCommand.h"

CCommand::ParamType CVarCommand::getReturnType() const
{
    switch(m_DataType)
    {
    case CValue::BOOLEAN:
        return CCommand::BOOLEAN_VAR;
    case CValue::NUMBER:
        return CCommand::NUMBER_VAR;
    case CValue::STRING:
        return CCommand::STRING_VAR;
    default:
        return CCommand::VOID;
    }
}

void CVarCommand::executeNextStep(CCommandExecuteThread &executionThread) const
{

}

void CVarCommand::setValue(CValue *value, CVarTable &varTable) const
{
    if(value == NULL || value->getDataType() != m_DataType)
        return;

    //给变量设值
   // varTable.setValue(m_qstrVarName, value);
}
