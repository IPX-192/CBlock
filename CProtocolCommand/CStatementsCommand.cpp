#include "CStatementsCommand.h"
#include "CMessage.h"
#include "CCommandExecuteThread.h"

CStatementsCommand::CStatementsCommand() {}

CStatementsCommand::~CStatementsCommand()
{
    qDeleteAll(m_listStatements);
}

void CStatementsCommand::executeNextStep(CCommandExecuteThread &executionThread) const
{
    IntMessage* message = (IntMessage*)executionThread.getMessage();

    //first step
    if(message == NULL) {
        message = new IntMessage();
        executionThread.setMessage(message);
    }

    //all statements executed
    if(message->getValue() >= m_listStatements.size()) {
        executionThread.endExecution(NULL);
        return;
    }

    //execute next statement
    CStatementCommand* nextBlock = m_listStatements.at(message->getValue());
    executionThread.setNextBlock(nextBlock);

    message->setValue(message->getValue()+1);
}

void CStatementsCommand::addStatement(CStatementCommand *statement)
{
    if(statement != NULL)
        m_listStatements.append(statement);
}
