#ifndef CVARCOMMANDBTN_H
#define CVARCOMMANDBTN_H

#include "CExpressionCommand.h"
#include "CValue.h"
#include "CVarTable.h"

class CVarCommandBtn : public CExpressionCommand
{
public:
    CVarCommandBtn();

    CVarCommandBtn(const QString& varName, CValue::DataType dataType) : _varName(varName), _dataType(dataType) {}

    virtual ~CVarCommandBtn() {}

    virtual QString getId() const {return QString("VarBlock");}

    virtual ParamType getReturnType() const;

    virtual QList<ParamType> getParamTypes() const {return QList<ParamType>();}

    virtual QString getParamDescription() const {return QString("");}

    virtual void executeNextStep(CCommandExecuteThread& executionThread) const;

    virtual void setValue(CValue* value, CVarTable& varTable) const;

    virtual bool addParameter(CCommand* parameter, int index) {return false;}

    virtual bool addBody(CExpressionCommand* body, int index) {return false;}


   // virtual CCommand* newInstance() const {return new CVarCommandBtn(_varName, _dataType);}


    virtual QString getVarName() const {return _varName;}

private:
    QString _varName;
    CValue::DataType _dataType;
};

#endif // CVARCOMMANDBTN_H
