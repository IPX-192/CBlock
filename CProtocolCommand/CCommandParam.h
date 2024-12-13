#ifndef CCOMMANDPARAM_H
#define CCOMMANDPARAM_H

#include "CCommand.h"
class CCommandBtn;

class CCommandParam
{
public:
    CCommandParam(CCommand::ParamType type);
    ~CCommandParam();

    CCommandBtn* getBlock() const { return m_CommandBtn; }

    CCommand::ParamType getParamType() const { return m_ParamType; }

    void setBlock(CCommandBtn* block);


private:
    CCommandBtn* m_CommandBtn;

    CCommand::ParamType m_ParamType;

};

#endif // CCOMMANDPARAM_H
