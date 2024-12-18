#ifndef CCOMMANDLIBRARY_H
#define CCOMMANDLIBRARY_H

#include <QList>
#include <QString>
#include "CCommand.h"

#include "Commands/bool/CIfCommandBtn.h"
#include "Commands/bool/CIfElseCommandBtn.h"
#include "Commands/bool/CWhileCommandBtn.h"
#include "Commands/bool/CForCommandBtn.h"
#include "Commands/number/CGreaterThanNumberCommand.h"

class CCommandBtnLibrary;
class CCommandLibrary
{
public:
    CCommandLibrary();
    ~CCommandLibrary();
    bool registerBlock(CCommand* block);

    CCommand* getBlockInstance(QString id) const;

    CCommandBtnLibrary* createBlockReprLibrary() const;

    bool contains(QString id);

    CCommand* get(QString id) const;

private:
    QList<CCommand*> m_listCommand;     //存储指向block对象指针的列表
};

#endif // CCOMMANDLIBRARY_H
