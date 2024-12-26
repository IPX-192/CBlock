#ifndef CVARCOMMANDBTN_H
#define CVARCOMMANDBTN_H

#include "CCommandRepr.h"

class CVarCommandBtn : public CCommandRepr
{
    Q_OBJECT
public:
    CVarCommandBtn(CCommand::ParamType returnType, QString varName);

    CVarCommandBtn(const CVarCommandBtn& block);

    QString getVarName() const {return m_qstrVarName;}



    virtual CVarCommandBtn* copy();

    virtual bool isVarBlockRepr() const { return true; }


public slots:
    void deleteVariable();

private:
    QString m_qstrVarName;

};

#endif // CVARCOMMANDBTN_H
