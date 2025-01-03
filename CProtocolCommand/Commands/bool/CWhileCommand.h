#ifndef CWHILECOMMAND_H
#define CWHILECOMMAND_H

#include "CStatementCommand.h"
#include "CExpressionCommand.h"

class CWhileCommand : public CStatementCommand
{
public:
    CWhileCommand(){}

    virtual ~CWhileCommand();

    virtual QString getId() const {return QString("while");}

    virtual QList<ParamType> getParamTypes() const;

    virtual int getNumBodies() const {return 1;}

    virtual QString getParamDescription() const {return QObject::tr("While") + QString(" %p");}

    virtual QString getBodiesDescription() const {return QObject::tr("Do") + QString(" %b");}

    virtual void executeNextStep(CCommandExecuteThread& executionThread) const;

    virtual bool addParameter(CCommand* parameter, int index);

    virtual bool addBody(CStatementCommand* body, int index);

    virtual CCommand* newInstance() const {return new CWhileCommand();}



private:
    CExpressionCommand* m_Condition{nullptr};   //参数块
    CStatementCommand* m_Body{nullptr};         //下一个执行块
};

#endif // CWHILECOMMAND_H
