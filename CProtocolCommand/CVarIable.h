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


class SimpleVariable : public CVarIable
{
public:

    SimpleVariable(QString name, CValue::DataType type, bool locked = false);


    SimpleVariable(const SimpleVariable &var);


    ~SimpleVariable();


    virtual QString getName() const { return m_qstrName; }


    virtual CValue* getValue() const { return m_Value; }

    virtual CValue::DataType getDataType() const { return m_DataType; }


    virtual void setValue(CValue* value);


    void forceValue(CValue* value);


    virtual CVarIable* copy() const { return new SimpleVariable(*this); }

private:

    QString m_qstrName;

    CValue* m_Value;

    CValue::DataType m_DataType;

    bool m_bLocked;
};

#endif // CVARIABLE_H
