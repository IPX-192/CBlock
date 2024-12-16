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
