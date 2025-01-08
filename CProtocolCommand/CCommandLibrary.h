#ifndef CCOMMANDLIBRARY_H
#define CCOMMANDLIBRARY_H

#include <QList>
#include <QString>
#include "CCommand.h"

#include "Commands/bool/CIfCommand.h"
#include "Commands/bool/CIfElseCommand.h"
#include "Commands/bool/CWhileCommand.h"
#include "Commands/bool/CForCommandBtn.h"
#include "Commands/bool/CElseCommand.h"
#include "Commands/number/CDivideCommand.h"
#include "Commands/number/CEqualNumberCommand.h"
#include "Commands/number/CGreaterThanNumberCommand.h"
#include "Commands/number/CLessThanNumberCommand.h"
#include "Commands/number/CMinusCommand.h"
#include "Commands/number/CMultiplyCommand.h"
#include "Commands/number/CNumberRassignment.h"
#include "Commands/number/CPlusCommand.h"
#include "Commands/sprite/CBlockSceneBGColorCommand.h"
#include "CCommandRepr.h"
#include "CStartCommand.h"


class CCommandReprLibrary;
class CCommandLibrary
{
public:
    CCommandLibrary();
    ~CCommandLibrary();
    bool registerBlock(CCommand* block);

    CCommand* getBlockInstance(QString id) const;

    CCommandReprLibrary* createBlockReprLibrary() const;

    bool contains(QString id);

    CCommand* get(QString id) const;

private:
    QList<CCommand*> m_listCommand;     //存储指向block对象指针的列表
};

#endif // CCOMMANDLIBRARY_H
