#ifndef CELSECOMMAND_H
#define CELSECOMMAND_H


#include "CStatementCommand.h"
#include "CExpressionCommand.h"

class CElseCommand : public CStatementCommand
{
public:
    CElseCommand();

    ~CElseCommand();

    virtual QString getId() const {return QString("else");}

    virtual QList<ParamType> getParamTypes() const;

    virtual int getNumBodies() const {return 1;}

    virtual QString getParamDescription() const {return QObject::tr("Else") + QString(" %p");}

    virtual QString getBodiesDescription() const {return QObject::tr("Then") + QString(" %b");}

    virtual void executeNextStep(CCommandExecuteThread& executionThread) const;

    virtual bool addParameter(CCommand* parameter, int index);

    virtual bool addBody(CStatementCommand* body, int index);

    virtual CCommand* newInstance() const {return new CElseCommand();}







private:
    CExpressionCommand* m_Condition{nullptr};   //参数块
    CStatementCommand* m_Body{nullptr};         //下一个执行块
};

#endif // CELSECOMMAND_H
