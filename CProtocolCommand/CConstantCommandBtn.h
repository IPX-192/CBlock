#ifndef CCONSTANTCOMMANDBTN_H
#define CCONSTANTCOMMANDBTN_H

#include "CCommandBtn.h"
#include "CCommandRepr.h"

class CConstantCommandBtn : public CCommandRepr
{
public:


    CConstantCommandBtn(CCommand::ParamType returnType, bool locked = false);

    CConstantCommandBtn(const CConstantCommandBtn& block);

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

#endif // CCONSTANTCOMMANDBTN_H
