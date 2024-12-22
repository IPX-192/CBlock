#ifndef CSTARTCOMMAND_H
#define CSTARTCOMMAND_H

#include "CEventCommand.h"

class CStartCommand : public CEventCommand
{
public:
    CStartCommand();

    ~CStartCommand(){}

    QString getId() const {return QString("Start");}

    virtual QList<ParamType> getParamTypes() const {return QList<ParamType>();}

    int getNumBodies() const {return 0;}

    QString getParamDescription() const {return QObject::tr("On Start");}

    QString getBodiesDescription() const {return QString("");}

    virtual void sendSignal(const CSignal& signal, CSprite* sprite);

    virtual bool addParameter(CCommand* parameter, int index) {return false;}

    virtual bool addBody(CStatementCommand* body, int index) {return false;}

    virtual CCommand* newInstance() const {return new CStartCommand();}

};

#endif // CSTARTCOMMAND_H
