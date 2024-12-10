#ifndef CVALUE_H
#define CVALUE_H

#include <QString>

class CValue
{
public:

    enum DataType {NUMBER, STRING, BOOLEAN};

    CValue();

    virtual ~CValue() {}

    virtual DataType getDataType() const = 0;


    virtual double toDouble() const = 0;

    virtual QString toString() const = 0;

    virtual bool toBool() const = 0;

    virtual CValue* copy() const = 0;

};

#endif // CVALUE_H
