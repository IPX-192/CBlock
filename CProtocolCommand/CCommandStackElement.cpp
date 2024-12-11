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

    ese->setMessage(NULL);
    ese->setBlock(m_Command);

    return ese;
}
