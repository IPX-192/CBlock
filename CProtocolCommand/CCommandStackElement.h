#ifndef CCOMMANDSTACKELEMENT_H
#define CCOMMANDSTACKELEMENT_H

#include "CMessage.h"
#include "CValue.h"
#include "CVarTable.h"
#include "CCommand.h"

class CCommandStackElement
{
public:
    CCommandStackElement() {}

    ~CCommandStackElement();

    CCommand* getBlock() const {return m_Command;}

    void setBlock(CCommand* command) {m_Command = command;}

    CMessage* getMessage() const {return m_Message;}

    void setMessage(CMessage* message);

    CCommandStackElement* getCopy() const;

private:
    CCommand* m_Command{nullptr};
    CMessage* m_Message{nullptr};
    CVarTable* m_VarTable{nullptr};
};

#endif // CCOMMANDSTACKELEMENT_H
