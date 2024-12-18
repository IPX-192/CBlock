#ifndef CMULTIPLYCOMMAND_H
#define CMULTIPLYCOMMAND_H
#include "CExpressionCommand.h"

class CMultiplyCommand:public CExpressionCommand
{
public:
    CMultiplyCommand();
    virtual ~ CMultiplyCommand();

    virtual QString getId() const {return QString("*");}

    virtual ParamType getReturnType() const {return CCommand::NUMBER_EXPRESSION;}

    virtual QList<ParamType> getParamTypes() const;

    virtual QString getParamDescription() const {return QString("%p * %p");}

    virtual void executeNextStep(CCommandExecuteThread& executionThread) const;

    virtual bool addParameter(CCommand* parameter, int index);

    virtual CCommand* newInstance() const {return new CMultiplyCommand();}

private:
    CExpressionCommand* m_Left{nullptr};
    CExpressionCommand* m_Right{nullptr};
};

#endif // CMULTIPLYCOMMAND_H
