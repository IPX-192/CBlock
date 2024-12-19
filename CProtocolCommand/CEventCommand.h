#ifndef CEVENTCOMMAND_H
#define CEVENTCOMMAND_H

#include "CCommand.h"
#include "CSignal.h"
#include "CObject.h"
class CStatementCommand;


//触发事件块，默认开始
class CEventCommand : public CCommand
{
public:
    CEventCommand();
    virtual ~CEventCommand();

    virtual QString getId() const = 0;

    ParamType getReturnType() const {return CCommand::EVENT;}

    virtual QList<ParamType> getParamTypes() const = 0;

    virtual int getNumBodies() const = 0;


    virtual QString getParamDescription() const = 0;

    virtual QString getBodiesDescription() const = 0;

    virtual void sendSignal(const CSignal& signal, CObject* sprite) = 0;

    virtual void executeNextStep(CCommandExecuteThread& executionThread) const {}

    virtual bool addParameter(CCommand* parameter, int index) = 0;

    virtual bool addBody(CStatementCommand* body, int index) = 0;


    CStatementCommand* getStatement() const {return m_Statement;}

    void setStatement(CStatementCommand* statement) {m_Statement = statement;}

    virtual CCommand* newInstance() const = 0;

private:
    CStatementCommand* m_Statement{nullptr};


};

#endif // CEVENTCOMMAND_H
