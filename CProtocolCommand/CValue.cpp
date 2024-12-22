#include "CValue.h"

CValue::CValue() {}

CValue *StringValue::copy() const
{
    StringValue* value = new StringValue(this->toString());
    return value;
}

CValue *NumberValue::copy() const
{
    NumberValue* value = new NumberValue(this->toDouble());
    return value;
}

CValue *BooleanValue::copy() const
{
    BooleanValue* value = new BooleanValue(this->toBool());
    return value;
}

SimpleValueList::SimpleValueList(QString name, CValue::DataType type)
    :m_qstrName(name),m_DataType(type)
{

}

SimpleValueList::SimpleValueList(const SimpleValueList &list)
    :CValueList(list)
{
    m_qstrName = list.getName();
    m_DataType = list.getDataType();

    for (int i = 0; i < list.getSize(); ++i) {
        m_listValues.append(list.getValueAt(i)->copy());
    }
}

SimpleValueList::~SimpleValueList()
{
    qDeleteAll(m_listValues);
    m_listValues.clear();
}

CValue *SimpleValueList::getValueAt(int pos) const
{
    if (pos >= 0 && pos < m_listValues.size())
        return m_listValues.at(pos);

    return NULL;
}

void SimpleValueList::setValueAt(int pos, CValue *value)
{
    if (value->getDataType() == m_DataType && (pos >= 0 && pos < m_listValues.size()))
    {
        if (m_listValues.at(pos) != NULL)
            delete m_listValues.at(pos);

        m_listValues.replace(pos, value);
    }

}

void SimpleValueList::addValue(CValue *value)
{
    if (value->getDataType() == m_DataType)
        m_listValues.append(value);
}
