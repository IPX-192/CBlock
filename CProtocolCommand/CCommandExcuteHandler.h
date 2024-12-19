#ifndef CCOMMANDEXCUTEHANDLER_H
#define CCOMMANDEXCUTEHANDLER_H

#include "CCommandExecuteThread.h"
#include <QObject>
#include <QThread>
#include <QList>
#include <QTimer>
#include <QDateTime>
#include "CObject.h"

class CCommandExcuteHandler : public QObject
{
    Q_OBJECT

public:
    CCommandExcuteHandler();

    ~CCommandExcuteHandler();

    void start();

    void stop();

    int getNumThreads() const;


    void addExecutionThread(CCommand* block,CVarTable* varTable);

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
};

#endif // CCOMMANDEXCUTEHANDLER_H
