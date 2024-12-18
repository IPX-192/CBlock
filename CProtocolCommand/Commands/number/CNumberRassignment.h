#ifndef CNUMBERRASSIGNMENT_H
#define CNUMBERRASSIGNMENT_H
#include "CExpressionCommand.h"
#include "CVarCommand.h"

class CNumberRassignment :public CExpressionCommand
{
public:
    CNumberRassignment();

    virtual ~CNumberRassignment();

    virtual QString getId() const {return QString("Set");}

    virtual ParamType getReturnType() const {return CCommand::NUMBER_EXPRESSION;}

    virtual QList<ParamType> getParamTypes() const;

    virtual QString getParamDescription() const {return QObject::tr("Set") + QString(" %p ") + QObject::tr("to") + QString(" %p");}

    virtual void executeNextStep(CCommandExecuteThread& executionThread) const;

    virtual bool addParameter(CCommand* parameter, int index);

    virtual CCommand* newInstance() const {return new CNumberRassignment();}

private:
    CVarCommand *m_VarCommand;
    CExpressionCommand* m_Expression{nullptr};
};

#endif // CNUMBERRASSIGNMENT_H
