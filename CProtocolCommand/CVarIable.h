#ifndef CVARIABLE_H
#define CVARIABLE_H

#include "CValue.h"
class CVarIable
{
public:
    CVarIable();
    ~CVarIable();

    virtual QString getName() const = 0;

    virtual CValue* getValue() const = 0;

    virtual CValue::DataType getDataType() const = 0;

    virtual void setValue(CValue* value) = 0;

    virtual CVarIable* copy() const = 0;
};

#endif // CVARIABLE_H
