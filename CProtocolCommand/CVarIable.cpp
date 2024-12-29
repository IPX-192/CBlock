#include "CVarIable.h"

CVarIable::CVarIable() {}

CVarIable::~CVarIable()
{

}

SimpleVariable::SimpleVariable(QString name, CValue::DataType type, bool locked)
    :m_qstrName(name),m_DataType(type),m_bLocked(locked)
{
    if (type == CValue::NUMBER)
        m_Value = new NumberValue(0.0);
    else if (type == CValue::STRING)
        m_Value = new StringValue("");
    else if (type == CValue::BOOLEAN)
        m_Value = new BooleanValue(false);
}

SimpleVariable::SimpleVariable(const SimpleVariable &var)
{
    m_qstrName = var.getName();
    m_DataType = var.getDataType();
    m_Value = var.getValue()->copy();
    m_bLocked = var.m_bLocked;
}

SimpleVariable::~SimpleVariable()
{
    if(m_Value != NULL)
        delete m_Value;
}

void SimpleVariable::setValue(CValue *value)
{
    if (m_bLocked || value->getDataType() != m_DataType) {
        if(value != NULL)
            delete value;
        return;
    }

    if (m_Value != NULL)
        delete m_Value;

    m_Value = value;
}

void SimpleVariable::forceValue(CValue *value)
{
    if (value->getDataType() != m_DataType)
        return;

    if (m_Value != NULL)
        delete m_Value;

    m_Value = value;
}
