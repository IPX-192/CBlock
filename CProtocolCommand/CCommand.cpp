#include "CCommand.h"

CCommand::CCommand() {}

bool CCommand::isValidParam(ParamType given, ParamType target)
{
    return true;
}

bool CCommand::isExpressionParam(ParamType paramType)
{
    return true;
}

bool CCommand::isVariableParam(ParamType paramType)
{
    return true;
}

bool CCommand::isListParam(ParamType paramType)
{
    return true;
}
