#ifndef CCOMMANDPARAM_H
#define CCOMMANDPARAM_H

#include "CCommand.h"
class CCommandRepr;

class CCommandParam
{
public:
    CCommandParam(CCommand::ParamType type);
    ~CCommandParam();

    CCommandRepr* getBlock() const { return m_CommandBtn; }

    CCommand::ParamType getParamType() const { return m_ParamType; }

    void setBlock(CCommandRepr* block);


private:
    CCommandRepr* m_CommandBtn;


    CCommand::ParamType m_ParamType;

};

#endif // CCOMMANDPARAM_H
