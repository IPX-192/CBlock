#ifndef CBLOCKSCENEBGCOLORCOMMAND_H
#define CBLOCKSCENEBGCOLORCOMMAND_H

#include "CCommandBtn.h"
#include "CStatementCommand.h"
#include "CExpressionCommand.h"

class CBlockSceneBGColorCommand : public CStatementCommand
{
public:
    CBlockSceneBGColorCommand();

    ~CBlockSceneBGColorCommand();

    virtual QString getId() const {return QString("set_color");}

    virtual QList<ParamType> getParamTypes() const;

    virtual int getNumBodies() const {return 0;}

    virtual QString getParamDescription() const {return QObject::tr("Set BlockScene Color:") + QString(" %p");}

    virtual QString getBodiesDescription() const {return QString("");}

    virtual void executeNextStep(CCommandExecuteThread& executionThread) const;

    virtual bool addParameter(CCommand* parameter, int index);

    virtual bool addBody(CStatementCommand* body, int index) {return false;}

    virtual CCommand* newInstance() const {return new CBlockSceneBGColorCommand();}


private:
    CExpressionCommand* m_SceneColor{nullptr};      //这两个物块实例化是varblock

};

#endif // CBLOCKSCENEBGCOLORCOMMAND_H
