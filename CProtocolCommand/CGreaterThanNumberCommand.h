#ifndef CGREATERTHANNUMBERCOMMAND_H
#define CGREATERTHANNUMBERCOMMAND_H

#include "CExpressionCommand.h"

class CGreaterThanNumberCommand :public CExpressionCommand
{
public:
    CGreaterThanNumberCommand();
    virtual ~CGreaterThanNumberCommand();

    virtual QString getId() const {return QString(">");}

    virtual ParamType getReturnType() const {return CCommand::BOOLEAN_EXPRESSION;}

    virtual QList<ParamType> getParamTypes() const;
    virtual QString getParamDescription() const {return QString("%p " + QObject::tr(">") + " %p");}
    virtual void executeNextStep(CCommandExecuteThread& executionThread) const;
    virtual bool addParameter(CCommand* parameter, int index);
    virtual CCommand* newInstance() const {return new CGreaterThanNumberCommand();}

private:
    CExpressionCommand* _left{nullptr};
    CExpressionCommand* _right{nullptr};
};

#endif // CGREATERTHANNUMBERCOMMAND_H
