#include "CSpriteRepr.h"

CSpriteRepr::CSpriteRepr(QString name)
    :m_qstrName(name)
{

}

CSpriteRepr::CSpriteRepr(const CSpriteRepr &sprite)
{
    m_qstrName= sprite.getName();
    foreach (CVarCommandRepr* var, sprite.getVars()) {
        m_listVars.append((CVarCommandRepr*) var->copy());
    }
}

CSpriteRepr::~CSpriteRepr()
{
    qDeleteAll(m_listVars);
}

void CSpriteRepr::setName(QString name)
{
    m_qstrName = name;
    emit nameChanged();
}

void CSpriteRepr::addVariable(CVarCommandRepr *var)
{
    m_listVars.append(var);
}

void CSpriteRepr::removeVariable(CVarCommandRepr *var)
{
    m_listVars.removeAll(var);
}

bool CSpriteRepr::hasVariableWithName(QString name)
{
    foreach(CVarCommandRepr* var, m_listVars)
    {
        if (var->getVarName() == name)
            return true;
    }

    return false;
}

