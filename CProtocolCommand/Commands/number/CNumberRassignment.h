#ifndef CNUMBERRASSIGNMENT_H
#define CNUMBERRASSIGNMENT_H
#include "CStatementCommand.h"
#include "CExpressionCommand.h"
#include "CVarCommand.h"

class CNumberRassignment :public CStatementCommand
{
public:
    CNumberRassignment();

    virtual ~CNumberRassignment();

    virtual QString getId() const {return QString("Set");}

    virtual QList<ParamType> getParamTypes() const;

    virtual int getNumBodies() const {return 0;}

    virtual QString getParamDescription() const {return QObject::tr("Set") + QString(" %p ") + QObject::tr("to") + QString(" %p");}

    virtual QString getBodiesDescription() const {return QString("");}

    virtual void executeNextStep(CCommandExecuteThread& executionThread) const;

    virtual bool addParameter(CCommand* parameter, int index);

    virtual bool addBody(CStatementCommand* body, int index) {return false;}

    virtual CCommand* newInstance() const {return new CNumberRassignment();}

private:
    CVarCommand *m_VarCommand;
    CExpressionCommand* m_Expression{nullptr};
};

#endif // CNUMBERRASSIGNMENT_H
