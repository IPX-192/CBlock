#ifndef CVARCOMMAND_H
#define CVARCOMMAND_H

#include "CExpressionCommand.h"
#include "CValue.h"
#include "CVarTable.h"

class CVarCommand  : public CExpressionCommand
{
public:
    CVarCommand();

public:

    CVarCommand(const QString& varName, CValue::DataType dataType) : m_qstrVarName(varName), m_DataType(dataType) {}

    virtual ~CVarCommand() {}

    virtual QString getId() const {return QString("VarBlock");}

    virtual ParamType getReturnType() const;

    virtual QList<ParamType> getParamTypes() const {return QList<ParamType>();}

    virtual QString getParamDescription() const {return QString("");}

    virtual void executeNextStep(CCommandExecuteThread& executionThread) const;

    virtual void setValue(CValue* value, CVarTable& varTable) const;

    virtual bool addParameter(CCommand* parameter, int index) {return false;}

    virtual bool addBody(CExpressionCommand* body, int index) {return false;}


    virtual CCommand* newInstance() const {return new CVarCommand(m_qstrVarName, m_DataType);}


    virtual QString getVarName() const {return m_qstrVarName;}

private:
    QString m_qstrVarName;
    CValue::DataType m_DataType;
};

#endif // CVARCOMMAND_H
