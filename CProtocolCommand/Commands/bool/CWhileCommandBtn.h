#ifndef CWHILECOMMANDBTN_H
#define CWHILECOMMANDBTN_H

#include "CStatementCommand.h"
#include "CExpressionCommand.h"

class CWhileCommandBtn : public CStatementCommand
{
public:
    CWhileCommandBtn(){}

    virtual ~CWhileCommandBtn();

    virtual QString getId() const {return QString("while");}

    virtual QList<ParamType> getParamTypes() const;

    virtual int getNumBodies() const {return 1;}

    virtual QString getParamDescription() const {return QObject::tr("While") + QString(" %p");}

    virtual QString getBodiesDescription() const {return QObject::tr("Do") + QString(" %b");}

    virtual void executeNextStep(CCommandExecuteThread& executionThread) const;

    virtual bool addParameter(CCommand* parameter, int index);

    virtual bool addBody(CStatementCommand* body, int index);

    virtual CCommand* newInstance() const {return new CWhileCommandBtn();}



private:
    CExpressionCommand* m_Condition{nullptr};   //参数块
    CStatementCommand* m_Body{nullptr};         //下一个执行块
};

#endif // CWHILECOMMANDBTN_H
