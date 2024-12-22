#ifndef CCOMMANDEXECUTETHREAD_H
#define CCOMMANDEXECUTETHREAD_H

#include <QStack>
#include <QString>
#include "CCommand.h"
#include "CValue.h"
#include "CMessage.h"
#include "CCommandStackElement.h"
#include "CSprite.h"

class CCommandExecuteThread
{
public:
    CCommandExecuteThread();

    CCommandExecuteThread(CCommand* block,CVarTable* varTable, CSprite* sprite);

    ~CCommandExecuteThread();

    bool isEmpty() const;

    void executeNext();

    void setNextBlock(CCommand* block);

    void setMessage(CMessage* message);

    CMessage* getMessage() const;

    void setVarTable(CVarTable* varTable);

    CVarTable* getVarTable() const;

    CSprite* getSprite() const;

    void setSprite(CSprite* sprite);

    void endExecution(CValue* returnValue);

    CValue* getReturnValue() const;

private:

    void changeTopBlock();


private:
    QStack<CCommandStackElement*> m_stackCommandStack;       //模拟程序执行栈
    CValue* m_ReturnValue{nullptr};                          //存储最后执行的代码块的返回值
    CCommand* m_NextBlock{nullptr};
    bool m_bKeepTopBlock{true};                              //在类的实现中控制是否保留执行栈的顶部代码块


    /**
     * @brief Changes the next block to be executed on the executionstack
     */

};

#endif // CCOMMANDEXECUTETHREAD_H
