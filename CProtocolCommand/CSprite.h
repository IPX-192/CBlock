#ifndef CSPRITE_H
#define CSPRITE_H

//控制的对象类

#include <QString>
#include "CVarTable.h"
#include "CEventCommand.h"

class CCommandExcuteHandler;

class CSprite
{
public:
    CSprite(SimpleVarTable* globalVars);

    ~CSprite();

    void addBlock(CEventCommand* block) { m_qlistEventCommand.append(block); }

    void setExecutionHandler(CCommandExcuteHandler* test);

    CCommandExcuteHandler* getExecutionHandler();

    SpriteVarTable* getVarTable() const { return m_SpriteVars; }

    void sendSignal(const CSignal &signal);

private:
    SpriteVarTable* m_SpriteVars;


    QList<CEventCommand*> m_qlistEventCommand;           //这个精灵有几个事件物块
    CCommandExcuteHandler* m_pExcuteHandler{nullptr};


    int m_iValue{0};
    QString m_strValue{""};
    bool m_bValue{false};

};

#endif // CSPRITE_H
