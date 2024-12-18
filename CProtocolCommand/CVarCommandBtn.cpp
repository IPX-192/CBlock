#include "CVarCommandBtn.h"

CVarCommandBtn::CVarCommandBtn(CCommand::ParamType returnType, QString varName)
    : CCommandBtn(returnType, varName), m_qstrVarName(varName)
{

}

CVarCommandBtn::CVarCommandBtn(const CVarCommandBtn &block)
    : CCommandBtn(block.getReturnType(), block.getVarName()), m_qstrVarName(block.m_qstrVarName)
{

}


CVarCommandBtn *CVarCommandBtn::copy()
{
    return new CVarCommandBtn(*this);
}

void CVarCommandBtn::deleteVariable()
{

}

