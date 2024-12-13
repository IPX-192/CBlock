#include "CCommand.h"

CCommand::CCommand() {}

CCommand::~CCommand()
{

}

bool CCommand::isValidParam(ParamType given, ParamType target)
{
    if(given == target)
    {
        return true;
    }
    if(given == BOOLEAN_VAR && target == BOOLEAN_EXPRESSION)
    {
        return true;
    }

    if(given == NUMBER_VAR && target == NUMBER_EXPRESSION)
    {
        return true;
    }

    if(given == STRING_VAR && target == STRING_EXPRESSION)
    {
        return true;
    }
    return false;
}

bool CCommand::isExpressionParam(ParamType paramType)
{
    return (paramType == BOOLEAN_EXPRESSION
            || paramType == NUMBER_EXPRESSION
            || paramType == STRING_EXPRESSION);
}

bool CCommand::isVariableParam(ParamType paramType)
{
    return (paramType == BOOLEAN_VAR
            || paramType == NUMBER_VAR
            || paramType == STRING_VAR);
}

bool CCommand::isListParam(ParamType paramType)
{
    return (paramType == BOOLEAN_LIST
            || paramType == NUMBER_LIST
            || paramType == STRING_LIST);
}
