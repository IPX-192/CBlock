#ifndef CVARCOMMANDBTN_H
#define CVARCOMMANDBTN_H

#include "CCommandBtn.h"

class CVarCommandBtn : public CCommandBtn
{
    Q_OBJECT
public:
    CVarCommandBtn(CCommand::ParamType returnType, QString varName);

    CVarCommandBtn(const CVarCommandBtn& block);

    QString getVarName() const {return _varName;}



    virtual CVarCommandBtn* copy();

    virtual bool isVarBlockRepr() const { return true; }


public slots:
    void deleteVariable();

private:
    QString _varName;

};

#endif // CVARCOMMANDBTN_H
