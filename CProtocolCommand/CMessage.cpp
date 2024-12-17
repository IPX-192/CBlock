#include "CMessage.h"

CMessage::CMessage() {}

ValueMessage::~ValueMessage()
{
    if(m_Value != NULL)
        delete m_Value;
}

void ValueMessage::setValue(CValue *value)
{
    if(m_Value != NULL)
        delete m_Value;
    m_Value = value;
}
