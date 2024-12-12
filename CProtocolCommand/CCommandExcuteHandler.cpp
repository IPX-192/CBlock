#include "CCommandExcuteHandler.h"

CCommandExcuteHandler::CCommandExcuteHandler() {


    m_bRunning = false;
    m_bWorking = false;
    m_qTimer = new QTimer();
    m_qTimer->setInterval(10);

    connect(m_qTimer, SIGNAL(timeout()), this, SLOT(onExecutionTick()));

}

CCommandExcuteHandler::~CCommandExcuteHandler()
{
    while(!m_listThreads.isEmpty()) {
        delete m_listThreads.first();
        m_listThreads.removeFirst();
    }

    delete m_qTimer;
}

void CCommandExcuteHandler::start()
{
    m_bRunning = true;

    m_qTimer->start();
}

int CCommandExcuteHandler::getNumThreads() const
{
    return m_listThreads.size();
}

//有几个事件命令就增加几个事件的处理线程
void CCommandExcuteHandler::addExecutionThread(CCommand *block)
{
    if(block == NULL )
        return;

    CCommandExecuteThread* thread = new CCommandExecuteThread(block);

    m_listThreads.append(thread);

}

void CCommandExcuteHandler::executeThreads()
{
    //放了物块这里就是赋值,执行了事件之后会删除
    if(m_listThreads.size() == 0)
    {
        //qDebug()<<u8"没得物块";
        return;
    }
    for(int i = m_listThreads.size()-1; i >= 0; i--) {
        CCommandExecuteThread* et = m_listThreads.at(i);
        et->executeNext();                  //重要：物块的关键应该是在这里执行的

        if(et->isEmpty()) {
            delete et;
            m_listThreads.removeAt(i);
        }
    }
}

void CCommandExcuteHandler::onExecutionTick()
{
    if(!m_bRunning)
        return;

    if(m_bWorking)
    {

        return;
    }

    m_bWorking = true;

    //QDateTime currentTime = QDateTime::currentDateTime();


    executeThreads();          //控制事件的信号,所有对物块的操作都在这里面
    //emit executionTicked();


    m_bWorking = false;
}
