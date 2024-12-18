#ifndef CLESSTHANNUMBERCOMMAND_H
#define CLESSTHANNUMBERCOMMAND_H

#include "CExpressionCommand.h"

class CLessthanNumberCommand :public CExpressionCommand
{
public:
    CLessthanNumberCommand();
    ~CLessthanNumberCommand();

    virtual QString getId() const {return QString("<");}

    virtual ParamType getReturnType() const {return CCommand::BOOLEAN_EXPRESSION;}

    virtual QList<ParamType> getParamTypes() const;

    virtual QString getParamDescription() const {return QString("%p " + QObject::tr("<") + " %p");}

    virtual void executeNextStep(CCommandExecuteThread& executionThread) const;

    virtual bool addParameter(CCommand* parameter, int index);

    virtual CCommand* newInstance() const {return new CLessthanNumberCommand();}

private:
    CExpressionCommand* m_Left{nullptr};
    CExpressionCommand* m_Right{nullptr};
};

#endif // CLESSTHANNUMBERCOMMAND_H
