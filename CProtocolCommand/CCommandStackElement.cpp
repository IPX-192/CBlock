#include "CCommandStackElement.h"

CCommandStackElement::~CCommandStackElement()
{
    if(m_Message != nullptr)
    {
        delete m_Message;
        m_Message = nullptr;
    }

}

void CCommandStackElement::setMessage(CMessage *message)
{
    if(m_Message != nullptr)
    {
        delete m_Message;
    }
    m_Message = message;
}

CCommandStackElement *CCommandStackElement::getCopy() const
{
    CCommandStackElement* ese = new CCommandStackElement();

    ese->setMessage(nullptr);
    ese->setBlock(m_Command);
    ese->setSprite(m_Sprite);
    ese->setVarTable(m_VarTable);

    return ese;
}
