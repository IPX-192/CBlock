#include "CCommandParam.h"

CCommandParam::CCommandParam(CCommand::ParamType type):m_CommandBtn(nullptr),m_ParamType(type)
{

}

CCommandParam::~CCommandParam()
{
    if(m_CommandBtn != nullptr)
    {
        delete m_CommandBtn;
        m_CommandBtn = nullptr;
    }
}

void CCommandParam::setBlock(CCommandBtn *block)
{
    m_CommandBtn = block;
}
