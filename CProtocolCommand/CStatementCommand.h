#ifndef CSTATEMENTCOMMAND_H
#define CSTATEMENTCOMMAND_H

#include "CCommand.h"

class CStatementCommand : public CCommand
{
public:
    CStatementCommand();

    virtual ~CStatementCommand() {}

    virtual QString getId() const = 0;

    ParamType getReturnType() const {return CCommand::VOID;}

    virtual QList<ParamType> getParamTypes() const = 0;

    virtual int getNumBodies() const = 0;

    virtual QString getParamDescription() const = 0;

    virtual QString getBodiesDescription() const = 0;

    virtual void executeNextStep(CCommandExecuteThread& executionThread) const = 0;

    virtual bool addParameter(CCommand* parameter, int index) = 0;

    virtual bool addBody(CStatementCommand* body, int index) = 0;

    virtual CCommand* newInstance() const = 0;

};

#endif // CSTATEMENTCOMMAND_H
