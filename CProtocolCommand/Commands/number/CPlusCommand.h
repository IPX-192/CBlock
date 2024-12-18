#ifndef CPLUSCOMMAND_H
#define CPLUSCOMMAND_H
#include "CExpressionCommand.h"
class CPlusCommand :public CExpressionCommand
{
public:
    CPlusCommand();

    virtual ~ CPlusCommand();

    virtual QString getId() const {return QString("+");}

    virtual ParamType getReturnType() const {return CCommand::NUMBER_EXPRESSION;}

    virtual QList<ParamType> getParamTypes() const;

    virtual QString getParamDescription() const {return QString("%p + %p");}

    virtual void executeNextStep(CCommandExecuteThread& executionThread) const;

    virtual bool addParameter(CCommand* parameter, int index);

    virtual CCommand* newInstance() const {return new CPlusCommand();}

private:
    CExpressionCommand* m_Left{nullptr};
    CExpressionCommand* m_Right{nullptr};
};

#endif // CPLUSCOMMAND_H
