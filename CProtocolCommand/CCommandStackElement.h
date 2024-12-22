#ifndef CCOMMANDSTACKELEMENT_H
#define CCOMMANDSTACKELEMENT_H

#include "CMessage.h"
#include "CValue.h"
#include "CVarTable.h"
#include "CCommand.h"
#include "CSprite.h"

class CCommandStackElement
{
public:
    CCommandStackElement() {}

    ~CCommandStackElement();

    CCommand* getBlock() const {return m_Command;}

    void setBlock(CCommand* command) {m_Command = command;}

    CMessage* getMessage() const {return m_Message;}

    void setMessage(CMessage* message);

    CVarTable* getVarTable() const {return m_VarTable;}

    void setVarTable(CVarTable* varTable) {m_VarTable = varTable;}

    CSprite* getSprite() const {return m_Sprite;}

    void setSprite(CSprite* sprite) {m_Sprite = sprite;}

    CCommandStackElement* getCopy() const;

private:
    CCommand* m_Command{nullptr};
    CMessage* m_Message{nullptr};
    CVarTable* m_VarTable{nullptr};
    CSprite* m_Sprite{nullptr};
};

#endif // CCOMMANDSTACKELEMENT_H
