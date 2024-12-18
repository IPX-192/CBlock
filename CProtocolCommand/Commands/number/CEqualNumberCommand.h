#ifndef CEQUALNUMBERCOMMAND_H
#define CEQUALNUMBERCOMMAND_H

#include "CExpressionCommand.h"

class CEqualNumberCommand :public CExpressionCommand
{
public:
    CEqualNumberCommand();

    virtual ~CEqualNumberCommand();

    virtual QString getId() const {return QString("=");}

    virtual ParamType getReturnType() const {return CCommand::BOOLEAN_EXPRESSION;}

    virtual QList<ParamType> getParamTypes() const;

    virtual QString getParamDescription() const {return QString("%p " + QObject::tr("equals") + " %p");}

    virtual void executeNextStep(CCommandExecuteThread& executionThread) const;

    virtual bool addParameter(CCommand* parameter, int index);

    virtual CCommand* newInstance() const {return new CEqualNumberCommand();}

private:
    CExpressionCommand* m_Left{nullptr};
    CExpressionCommand* m_Right{nullptr};


};

#endif // CEQUALNUMBERCOMMAND_H
