#include "CVarCommandBtn.h"

CVarCommandBtn::CVarCommandBtn() {}

CCommand::ParamType CVarCommandBtn::getReturnType() const
{
    switch(_dataType)
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

void CVarCommandBtn::executeNextStep(CCommandExecuteThread &executionThread) const
{

}

void CVarCommandBtn::setValue(CValue *value, CVarTable &varTable) const
{

}
