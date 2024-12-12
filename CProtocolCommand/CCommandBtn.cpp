#include "CCommandBtn.h"


CCommandBtn::CCommandBtn(CCommand *block)
{
    m_qstrID = block->getId();
}

CCommandBtn::~CCommandBtn()
{

}

CCommandBtn *CCommandBtn::copy()
{
    return new CCommandBtn(*this);
}
