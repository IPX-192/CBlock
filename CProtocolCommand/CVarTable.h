#ifndef CVARTABLE_H
#define CVARTABLE_H

#include "CValue.h"
#include "CVarIable.h"

class CVarTable
{
public:
    CVarTable();

    ~CVarTable();

    virtual CValue* getValue(QString name) const = 0;

    virtual bool setValue(QString name, CValue* value) = 0;

    virtual void addVariable(CVarIable* var) = 0;

    virtual CVarTable* getVariable(QString name) const = 0;

    virtual ValueList* getList(QString name) const = 0;

    virtual void addList(ValueList* list) = 0;

    virtual CVarTable* copy() = 0;
};

// class SimpleVarTable : public CVarTable
// {
// public:

//     SimpleVarTable();


//     virtual ~SimpleVarTable();


//     virtual CValue* getValue(QString name) const;


//     virtual bool setValue(QString name, CValue* value);


//     virtual void addVariable(CVarIable* variable);


//     virtual CVarIable* getVariable(QString name) const;


//     virtual ValueList* getList(QString name) const;


//     virtual void addList(ValueList* list);


//     CVarTable *copy();


//     QList<CVarIable*> getVariables() const { return m_listIable; }


//     QList<ValueList*> getLists() const { return m_listValue; }

// private:
//     QList<CVarIable*> m_listIable;

//     QList<ValueList*> m_listValue;
// };


#endif // CVARTABLE_H
