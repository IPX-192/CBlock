#ifndef CCOMMANDLIBRARY_H
#define CCOMMANDLIBRARY_H

#include <QList>
#include <QString>
#include "CCommand.h"
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
};

#endif // CCOMMANDLIBRARY_H
