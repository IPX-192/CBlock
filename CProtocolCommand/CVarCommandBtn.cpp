#include "CVarCommandBtn.h"

CVarCommandBtn::CVarCommandBtn(CCommand::ParamType returnType, QString varName, bool locked)
    : CCommandRepr(returnType, varName, locked), m_qstrVarName(varName)
{

}

CVarCommandBtn::CVarCommandBtn(const CVarCommandBtn &block)
    : CCommandRepr(block.getReturnType(), block.getVarName(), block.isLocked()), m_qstrVarName(block.m_qstrVarName)
{

}


CVarCommandBtn *CVarCommandBtn::copy()
{
    return new CVarCommandBtn(*this);
}

void CVarCommandBtn::deleteVariable()
{

}

