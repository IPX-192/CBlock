#ifndef CVARCOMMANDREPR_H
#define CVARCOMMANDREPR_H

#include "CCommandRepr.h"

class CVarCommandRepr : public CCommandRepr
{
    Q_OBJECT
public:
    CVarCommandRepr(CCommand::ParamType returnType, QString varName, bool locked = false);

    CVarCommandRepr(const CVarCommandRepr& block);

    QString getVarName() const {return m_qstrVarName;}


    virtual CVarCommandRepr* copy();

    virtual bool isVarBlockRepr() const { return true; }


public slots:
    void deleteVariable();

private:
    QString m_qstrVarName;

};

#endif // CVARCOMMANDREPR_H
