#include "CConstantCommandBtn.h"

CConstantCommandBtn::CConstantCommandBtn(CCommand::ParamType returnType)
    : CCommandBtn(returnType), m_Value(0)
{
    if(returnType == CCommand::STRING_EXPRESSION)
    {
        m_Value.setValue(QString(tr("text")));
    }

}

CConstantCommandBtn::CConstantCommandBtn(const CConstantCommandBtn &block): CCommandBtn(block.getReturnType()), m_Value(block.getValue())
{

}



CCommandBtn *CConstantCommandBtn::copy()
{
    return new CConstantCommandBtn(*this);
}
