#ifndef CIFCOMMANDBTN_H
#define CIFCOMMANDBTN_H

#include "CCommandBtn.h"
#include "CStatementCommand.h"
#include "CExpressionCommand.h"

class CIfCommandBtn : public CStatementCommand
{
public:
    CIfCommandBtn();

    ~CIfCommandBtn();

    virtual QString getId() const {return QString("Control_IfBlock");}

    virtual QList<ParamType> getParamTypes() const;

    virtual int getNumBodies() const {return 1;}

    virtual QString getParamDescription() const {return QObject::tr("If") + QString(" %p");}

    virtual QString getBodiesDescription() const {return QObject::tr("Then") + QString(" %b");}

    virtual void executeNextStep(CCommandExecuteThread& executionThread) const;

    virtual bool addParameter(CCommand* parameter, int index);

    virtual bool addBody(CStatementCommand* body, int index);

    virtual CCommand* newInstance() const {return new CIfCommandBtn();}







private:
    CCommandBtn* m_body;

};

#endif // CIFCOMMANDBTN_H
