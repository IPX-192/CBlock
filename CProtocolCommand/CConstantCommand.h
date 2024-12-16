#ifndef CCONSTANTCOMMAND_H
#define CCONSTANTCOMMAND_H

#include "CExpressionCommand.h"
#include "CValue.h"

class CConstantCommand : public CExpressionCommand
{
public:
    CConstantCommand(CValue* value) : m_Value(value) {}
    virtual ~CConstantCommand();

    virtual QString getId() const {return QString("ConstantBlock");}

    virtual ParamType getReturnType() const;

    virtual QList<ParamType> getParamTypes() const {return QList<ParamType>();}

    virtual QString getParamDescription() const {return QString("");}

    virtual void executeNextStep(CCommandExecuteThread& executionThread) const;

    virtual bool addParameter(CCommand* parameter, int index) {return false;}

    virtual bool addBody(CStatementCommand* body, int index) {return false;}

    virtual CCommand* newInstance() const {return new CConstantCommand(NULL);}
private:
    CValue* m_Value;
};

#endif // CCONSTANTCOMMAND_H
