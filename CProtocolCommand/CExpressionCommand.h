#ifndef CEXPRESSIONCOMMAND_H
#define CEXPRESSIONCOMMAND_H

#include "CCommand.h"

class CExpressionCommand : public CCommand
{
public:
    CExpressionCommand();

    virtual ~CExpressionCommand() {}

    virtual QString getId() const = 0;

    virtual ParamType getReturnType() const = 0;

    virtual QList<ParamType> getParamTypes() const = 0;

    int getNumBodies() const {return 0;}

    virtual QString getParamDescription() const = 0;

    QString getBodiesDescription() const {return QString("");}

    virtual void executeNextStep(CCommandExecuteThread& executionThread) const = 0;

    virtual bool addParameter(CCommand* parameter, int index) = 0;

    bool addBody(CExpressionCommand* body, int index) {return false;}

    virtual CCommand* newInstance() const = 0;

};

#endif // CEXPRESSIONCOMMAND_H
