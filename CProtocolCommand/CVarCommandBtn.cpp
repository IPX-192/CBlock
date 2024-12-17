#include "CVarCommandBtn.h"

CVarCommandBtn::CVarCommandBtn(CCommand::ParamType returnType, QString varName)
    : CCommandBtn(returnType, varName), _varName(varName)
{

}

CVarCommandBtn::CVarCommandBtn(const CVarCommandBtn &block)
    : CCommandBtn(block.getReturnType(), block.getVarName()), _varName(block._varName)
{

}


CVarCommandBtn *CVarCommandBtn::copy()
{
    return new CVarCommandBtn(*this);
}

void CVarCommandBtn::deleteVariable()
{

}

