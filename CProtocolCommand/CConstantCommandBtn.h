#ifndef CCONSTANTCOMMANDBTN_H
#define CCONSTANTCOMMANDBTN_H

#include "CCommandBtn.h"

class CConstantCommandBtn : public CCommandBtn
{
public:


    CConstantCommandBtn(CCommand::ParamType returnType);

    CConstantCommandBtn(const CConstantCommandBtn& block);

    virtual CCommandBtn* copy();

    virtual bool isConstantBlockRepr() const { return true; }

      QVariant getValue() const {return m_Value;}

    void setValue(QVariant value) {m_Value = value;}

private:
    QVariant m_Value;
};

#endif // CCONSTANTCOMMANDBTN_H
