#ifndef CIFELSECOMMAND_H
#define CIFELSECOMMAND_H

#include "CCommandBtn.h"
#include "CStatementCommand.h"
#include "CExpressionCommand.h"

class CIfElseCommand: public CStatementCommand
{
public:
    CIfElseCommand();

    ~CIfElseCommand();

    virtual QString getId() const {return QString("if_else");}

    virtual QList<ParamType> getParamTypes() const;

    virtual int getNumBodies() const {return 2;}

    virtual QString getParamDescription() const {return QObject::tr("If") + QString(" %p");}

    virtual QString getBodiesDescription() const {return QObject::tr("Then") + QString(" %b ") + QObject::tr("Else") + QString(" %b");}

    virtual void executeNextStep(CCommandExecuteThread& executionThread) const;

    virtual bool addParameter(CCommand* parameter, int index);

    virtual bool addBody(CStatementCommand* body, int index);

    virtual CCommand* newInstance() const {return new CIfElseCommand();}


private:
    CExpressionCommand* m_Condition;
    CStatementCommand* m_IfBody;
    CStatementCommand* m_ElseBody;
};

#endif // CIFELSECOMMAND_H
