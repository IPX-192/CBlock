#include "CVarCommandRepr.h"

CVarCommandRepr::CVarCommandRepr(CCommand::ParamType returnType, QString varName, bool locked)
    : CCommandRepr(returnType, varName, locked), m_qstrVarName(varName)
{

}

CVarCommandRepr::CVarCommandRepr(const CVarCommandRepr &block)
    : CCommandRepr(block.getReturnType(), block.getVarName(), block.isLocked()), m_qstrVarName(block.m_qstrVarName)
{

}


CVarCommandRepr *CVarCommandRepr::copy()
{
    return new CVarCommandRepr(*this);
}

void CVarCommandRepr::deleteVariable()
{

}

