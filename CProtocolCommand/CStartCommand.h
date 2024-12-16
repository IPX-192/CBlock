#ifndef CSTARTCOMMAND_H
#define CSTARTCOMMAND_H

#include "CCommand.h"

class CStartCommand
{
public:
    CStartCommand();

    ~CStartCommand(){}

    QString getId() const {return QString("Event_StartEventBlock");}

    int getNumBodies() const {return 0;}

    QString getParamDescription() const {return QObject::tr("On Start");}

    QString getBodiesDescription() const {return QString("");}

};

#endif // CSTARTCOMMAND_H
