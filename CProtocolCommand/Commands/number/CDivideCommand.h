#ifndef CDIVIDECOMMAND_H
#define CDIVIDECOMMAND_H


#include "CExpressionCommand.h"


//除法运算
class CDivideCommand:public CExpressionCommand
{
public:
    CDivideCommand();
    virtual ~CDivideCommand();

    virtual QString getId() const {return QString("/");}

    virtual ParamType getReturnType() const {return CCommand::NUMBER_EXPRESSION;}

    virtual QList<ParamType> getParamTypes() const;

    virtual QString getParamDescription() const {return QString("%p / %p");}

    virtual void executeNextStep(CCommandExecuteThread& executionThread) const;

    virtual bool addParameter(CCommand* parameter, int index);

    virtual CCommand* newInstance() const {return new CDivideCommand();}


private:
    CExpressionCommand* m_Left{nullptr};
    CExpressionCommand* m_Right{nullptr};

};

#endif // CDIVIDECOMMAND_H
