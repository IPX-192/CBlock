#ifndef CLessThanNumberCommand_H
#define CLessThanNumberCommand_H

#include "CExpressionCommand.h"

class CLessThanNumberCommand :public CExpressionCommand
{
public:
    CLessThanNumberCommand();
    ~CLessThanNumberCommand();

    virtual QString getId() const {return QString("<");}

    virtual ParamType getReturnType() const {return CCommand::BOOLEAN_EXPRESSION;}

    virtual QList<ParamType> getParamTypes() const;

    virtual QString getParamDescription() const {return QString("%p " + QObject::tr("<") + " %p");}

    virtual void executeNextStep(CCommandExecuteThread& executionThread) const;

    virtual bool addParameter(CCommand* parameter, int index);

    virtual CCommand* newInstance() const {return new CLessThanNumberCommand();}

private:
    CExpressionCommand* m_Left{nullptr};
    CExpressionCommand* m_Right{nullptr};
};

#endif // CLessThanNumberCommand_H
