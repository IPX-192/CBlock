#include "CCommandExcuteHandler.h"
#include <QDebug>

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
    _prevDrawTime = QDateTime::currentDateTime();
    _prevExecutionTime = QDateTime::currentDateTime();
    m_bRunning = true;
    m_qTimer->start();
}

void CCommandExcuteHandler::stop()
{
    m_bRunning = false;

    m_qTimer->stop();
}

int CCommandExcuteHandler::getNumThreads() const
{
    return m_listThreads.size();
}

void CCommandExcuteHandler::addExecutionThread(CCommand *block, CVarTable *varTable, CSprite *sprite)
{
    if(block == nullptr || varTable == nullptr || sprite == nullptr)
    {
        return;
    }

    CCommandExecuteThread* thread = new CCommandExecuteThread(block, varTable, sprite);

    m_listThreads.append(thread);
}

void CCommandExcuteHandler::executeThreads()
{
    //放了物块这里就是赋值,执行了事件之后会删除
    if(m_listThreads.size() == 0)
    {
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

    if(EXECUTION_TICK_INTERVAL <= _prevExecutionTime.msecsTo(QDateTime::currentDateTime()))
    {
        executeThreads();          //控制事件的信号,所有对物块的操作都在这里面
        _prevExecutionTime = _prevExecutionTime.addMSecs(EXECUTION_TICK_INTERVAL);
    }

    if(DRAW_TICK_INTERVAL <= _prevDrawTime.msecsTo(QDateTime::currentDateTime()))
    {
        emit sigDrawingTicked();      //控制绘画的信号
        _prevDrawTime = _prevDrawTime.addMSecs(DRAW_TICK_INTERVAL);
    }

    m_bWorking = false;
}
