#ifndef CCONSTANTCOMMANDREPR_H
#define CCONSTANTCOMMANDREPR_H

#include "CCommandBtn.h"
#include "CCommandRepr.h"

class CConstantCommandRepr : public CCommandRepr
{
public:


    CConstantCommandRepr(CCommand::ParamType returnType, bool locked = false);

    CConstantCommandRepr(const CConstantCommandRepr& block);

    virtual CCommandRepr* copy();

    virtual bool isConstantBlockRepr() const { return true; }

    QVariant getValue() const {return m_Value;}

    void setValue(QVariant value);

    virtual QSize getTotalSize();
    virtual QSize getSize();
    virtual QSize getHeaderSize();

private:
    QVariant m_Value;
};

#endif // CCONSTANTCOMMANDREPR_H
