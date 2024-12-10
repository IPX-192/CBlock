#ifndef CCOMMANDSTACK_H
#define CCOMMANDSTACK_H

#include "CMessage.h"
#include "CValue.h"
#include "CCommandStackElement.h"
#include "CVarTable.h"

class CCommandStack
{
public:
    CCommandStack();

    ~CCommandStack();

    bool isEmpty() const;

    void executeNext();

    void setNextBlock();

    void setMessage(CMessage* message);


    CMessage* getMessage() const;

    void setVarTable(CVarTable* varTable);

    CVarTable* getVarTable() const;

    void endExecution(CValue* returnValue);

    CValue* getReturnValue() const;


private:
  //  QStack<CCommandStackElement*> _executionStack;     //模拟程序执行栈
    CValue* _returnValue;                                //存储最后执行的代码块的返回值
  // Block* _nextBlock;
    bool _keepTopBlock;                                 //在类的实现中控制是否保留执行栈的顶部代码块


};

#endif // CCOMMANDSTACK_H
