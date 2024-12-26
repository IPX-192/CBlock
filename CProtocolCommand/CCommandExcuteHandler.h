#ifndef CCOMMANDEXCUTEHANDLER_H
#define CCOMMANDEXCUTEHANDLER_H

#include "CCommandExecuteThread.h"
#include <QObject>
#include <QThread>
#include <QList>
#include <QTimer>
#include <QDateTime>

class CCommandExcuteHandler : public QObject
{
    Q_OBJECT

public:

    static const int EXECUTION_TICK_INTERVAL = 5;

    static const int DRAW_TICK_INTERVAL = 500;

    CCommandExcuteHandler();

    ~CCommandExcuteHandler();

    void start();

    void stop();

    int getNumThreads() const;


    void addExecutionThread(CCommand* block,CVarTable* varTable, CSprite* sprite);

    bool isRunning() const { return m_bRunning; }


private:
    void executeThreads();

public slots:

    void onExecutionTick();

signals:

    void sigDrawingTicked();



private:
    QList<CCommandExecuteThread*> m_listThreads;

    QTimer* m_qTimer;
    bool m_bRunning;
    bool m_bWorking;


    QDateTime _prevExecutionTime;
    QDateTime _prevDrawTime;
};

#endif // CCOMMANDEXCUTEHANDLER_H
