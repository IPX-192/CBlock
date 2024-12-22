#include "CVarTable.h"

CVarTable::CVarTable() {}

CVarTable::~CVarTable()
{

}

SimpleVarTable::SimpleVarTable()
{

}

SimpleVarTable::~SimpleVarTable()
{
    qDeleteAll(m_listValue);
    qDeleteAll(m_listIable);
}

CValue *SimpleVarTable::getValue(QString name) const
{
    foreach (CVarIable* var, m_listIable) {
        if (var->getName() == name)
            return var->getValue();
    }

    return NULL;
}

bool SimpleVarTable::setValue(QString name, CValue* value)
{
    foreach (CVarIable* var, m_listIable) {
        if (var->getName() == name) {
            var->setValue(value);
            return true;
        }
    }

    return false;
}


void SimpleVarTable::addVariable(CVarIable *variable)
{
    foreach (CVarIable* var, m_listIable) {
        if (var->getName() == variable->getName())
            return;
    }

    m_listIable.append(variable);
}

CVarIable *SimpleVarTable::getVariable(QString name) const
{
    foreach (CVarIable* var, m_listIable) {
        if (var->getName() == name)
            return var;
    }

    return NULL;
}

CValueList *SimpleVarTable::getList(QString name) const
{
    foreach (CValueList* list, m_listValue) {
        if (list->getName() == name)
            return list;
    }

    return NULL;
}

void SimpleVarTable::addList(CValueList *list)
{
    foreach (CValueList* l, m_listValue) {
        if (l->getName() == list->getName())
            return;
    }

    m_listValue.append(list);
}

CVarTable *SimpleVarTable::copy()
{
    SimpleVarTable* vartable = new SimpleVarTable;

    foreach (CVarIable* var, m_listIable) {
        vartable->addVariable(var->copy());
    }

    foreach (CValueList* list, m_listValue) {
        vartable->addList(list->copy());
    }

    return vartable;
}

SpriteVarTable::SpriteVarTable(SimpleVarTable *globals)
{
    m_GpriteVars = new SimpleVarTable;
}

SpriteVarTable::~SpriteVarTable()
{
    delete m_GpriteVars;
}

CValue *SpriteVarTable::getValue(QString name) const
{
    CValue* val = m_GpriteVars->getValue(name);

    if (val == nullptr)
        val = m_GpriteVars->getValue(name);

    return val;
}

bool SpriteVarTable::setValue(QString name, CValue *value)
{
    bool result = m_GpriteVars->setValue(name, value);

    if (!result)
        result = m_GlobalVars->setValue(name, value);

    return result;
}

void SpriteVarTable::addVariable(CVarIable *variable)
{
    m_GpriteVars->addVariable(variable);
}

CVarIable *SpriteVarTable::getVariable(QString name) const
{
    CVarIable* var = m_GpriteVars->getVariable(name);
    if (var == nullptr)
    {
        var = m_GlobalVars->getVariable(name);
    }

    return var;
}

CValueList *SpriteVarTable::getList(QString name) const
{
    CValueList* list = m_GpriteVars->getList(name);

    if (list == nullptr)
    {
        list = m_GlobalVars->getList(name);
    }

    return list;
}

void SpriteVarTable::addList(CValueList *list)
{
    m_GlobalVars->addList(list);
}

CVarTable *SpriteVarTable::copy()
{
    SpriteVarTable* vartable = new SpriteVarTable((SimpleVarTable*) m_GlobalVars->copy());
    vartable->setSpriteVars((SimpleVarTable*) m_GlobalVars->copy());
    return vartable;
}
