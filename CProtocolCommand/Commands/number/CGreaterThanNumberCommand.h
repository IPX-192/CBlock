#ifndef CGREATERTHANNUMBERCOMMAND_H
#define CGREATERTHANNUMBERCOMMAND_H

#include "CExpressionCommand.h"


//大于运算
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
    CExpressionCommand* m_Left{nullptr};
    CExpressionCommand* m_Right{nullptr};
};

#endif // CGREATERTHANNUMBERCOMMAND_H
