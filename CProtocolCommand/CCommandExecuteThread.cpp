#include "CCommandExecuteThread.h"
#include <QDebug>

CCommandExecuteThread::CCommandExecuteThread()
{

}

CCommandExecuteThread::CCommandExecuteThread(CCommand *block, CVarTable *varTable, CSprite *sprite)
{
    CCommandStackElement* ese = new CCommandStackElement();
    ese->setBlock(block);
    ese->setVarTable(varTable);
    ese->setSprite(sprite);
    m_stackCommandStack.push(ese);
}

CCommandExecuteThread::~CCommandExecuteThread()
{
    while(!m_stackCommandStack.isEmpty())
    {
        delete m_stackCommandStack.pop();
    }
    if(m_ReturnValue != nullptr)
    {
        delete m_ReturnValue;
        m_ReturnValue = nullptr;
    }
}

bool CCommandExecuteThread::isEmpty() const
{
    return m_stackCommandStack.isEmpty();
}

void CCommandExecuteThread::executeNext()
{
    //do nothing if stack is empty
    if(m_stackCommandStack.isEmpty())
    {
        return;
    }
    m_bKeepTopBlock = true;
    m_NextBlock = nullptr;

    m_stackCommandStack.top()->getBlock()->executeNextStep(*this);  //重要：执行物块代码的是这里，最顶部的物块这里是实例化的x和y。

    //if top block ended execution -> pop block

    if(!m_bKeepTopBlock)
        delete m_stackCommandStack.pop();
    //if top block did not end execution -> delete returnValue and set next block to execute
    else
    {
        if(m_ReturnValue != nullptr)
        {
            delete m_ReturnValue;
            m_ReturnValue = nullptr;
        }

        changeTopBlock();     //重要：不改变最上面执行的物块也不会一直执行
    }
}

void CCommandExecuteThread::setNextBlock(CCommand *block)
{
    m_NextBlock = block;

    //if execution stack is empty -> set block on stack immediately
    if(m_stackCommandStack.isEmpty())
        changeTopBlock();
}

void CCommandExecuteThread::setMessage(CMessage *message)
{
    if(message == nullptr)
        return;

    if(!m_stackCommandStack.isEmpty())
    {
        m_stackCommandStack.top()->setMessage(message);
    }
    else
    {
        delete message;
    }
}

CMessage *CCommandExecuteThread::getMessage() const
{
    if(m_stackCommandStack.isEmpty())
        return nullptr;

    return m_stackCommandStack.top()->getMessage();
}

void CCommandExecuteThread::setVarTable(CVarTable *varTable)
{
    if(!m_stackCommandStack.isEmpty())
        m_stackCommandStack.top()->setVarTable(varTable);
}

CVarTable *CCommandExecuteThread::getVarTable() const
{
    if(m_stackCommandStack.isEmpty())
        return NULL;

    return m_stackCommandStack.top()->getVarTable();
}

CSprite *CCommandExecuteThread::getSprite() const
{
    if(m_stackCommandStack.isEmpty())
        return NULL;

    return m_stackCommandStack.top()->getSprite();
}

void CCommandExecuteThread::setSprite(CSprite *sprite)
{
    if(!m_stackCommandStack.isEmpty())
        m_stackCommandStack.top()->setSprite(sprite);
}

void CCommandExecuteThread::endExecution(CValue *returnValue)
{
    if(m_ReturnValue != nullptr)
        delete m_ReturnValue;

    m_ReturnValue = returnValue;
    m_bKeepTopBlock = false;
}

CValue *CCommandExecuteThread::getReturnValue() const
{
    return m_ReturnValue;
}

void CCommandExecuteThread::changeTopBlock()
{
    //change nothing if nextBlock is NULL or already on top
    if(m_NextBlock ==NULL || (!m_stackCommandStack.isEmpty() && m_stackCommandStack.top()->getBlock() == m_NextBlock))
        return;

    //create new stackElement
    CCommandStackElement* ese;
    if(m_stackCommandStack.isEmpty())
        ese = new CCommandStackElement();
    else
        ese = m_stackCommandStack.top()->getCopy();

    ese->setBlock(m_NextBlock);

    m_stackCommandStack.push(ese);
}
