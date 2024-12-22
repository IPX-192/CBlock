#ifndef CVARTABLE_H
#define CVARTABLE_H

#include "CValue.h"
#include "CVarIable.h"
#include <QList>

class CVarTable
{
public:
    CVarTable();

    ~CVarTable();

    virtual CValue* getValue(QString name) const = 0;

    virtual bool setValue(QString name, CValue* value) = 0;

    virtual void addVariable(CVarIable* var) = 0;

    virtual CVarIable* getVariable(QString name) const = 0;

    virtual CValueList* getList(QString name) const = 0;

    virtual void addList(CValueList* list) = 0;

    virtual CVarTable* copy() = 0;
};

class SimpleVarTable : public CVarTable
{
public:

    SimpleVarTable();


    virtual ~SimpleVarTable();


    virtual CValue* getValue(QString name) const;


    virtual bool setValue(QString name, CValue* value);


    virtual void addVariable(CVarIable* variable);


    virtual CVarIable* getVariable(QString name) const;


    virtual CValueList* getList(QString name) const;


    virtual void addList(CValueList* list);


    CVarTable *copy();


    QList<CVarIable*> getVariables() const { return m_listIable; }


private:
    QList<CVarIable*> m_listIable;
    QList<CValueList*> m_listValue;

};

class SpriteVarTable : public CVarTable
{
public:

    SpriteVarTable(SimpleVarTable* globals);


    virtual ~SpriteVarTable();


    virtual CValue* getValue(QString name) const;


    virtual bool setValue(QString name, CValue* value);


    virtual void addVariable(CVarIable* variable);

    virtual CVarIable* getVariable(QString name) const;


    virtual CValueList* getList(QString name) const;


    virtual void addList(CValueList* list);

    virtual CVarTable *copy();

    /**
     * @brief Sets the sprite vars
     * @param vars The sprite vars
     */
    void setSpriteVars(SimpleVarTable* vars) { m_GpriteVars = vars; }

    /**
     * @brief Getter for the sprite vars
     * @return The sprite var table
     */
    SimpleVarTable* getSpriteVars() const { return m_GpriteVars; }

private:
    SimpleVarTable* m_GlobalVars;

    SimpleVarTable* m_GpriteVars;
};


#endif // CVARTABLE_H
