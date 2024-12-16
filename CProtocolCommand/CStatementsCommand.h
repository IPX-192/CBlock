#ifndef CSTATEMENTSCOMMAND_H
#define CSTATEMENTSCOMMAND_H

#include "CStatementCommand.h"

class CStatementsCommand : public CStatementCommand
{
public:
    CStatementsCommand();
    ~CStatementsCommand();

    virtual QString getId() const {return QString("StatementsBlock");}

    virtual QList<ParamType> getParamTypes() const {return QList<ParamType>();}

    virtual int getNumBodies() const {return 0;}

    virtual QString getParamDescription() const {return QString("");}

    virtual QString getBodiesDescription() const {return QString("");}

    virtual void executeNextStep(CCommandExecuteThread& executionThread) const;

    virtual void addStatement(CStatementCommand* statement);

    virtual bool addParameter(CCommand* parameter, int index) {return false;}

    virtual bool addBody(CStatementCommand* body, int index) {return false;}

    virtual CCommand* newInstance() const {return new CStatementsCommand();}

private:
    QList<CStatementCommand*> m_listStatements;

};

#endif // CSTATEMENTSCOMMAND_H
