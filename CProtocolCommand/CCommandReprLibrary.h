#ifndef CCOMMANDREPRLIBRARY_H
#define CCOMMANDREPRLIBRARY_H

#include <QList>
#include <QStringList>
#include "CCommandRepr.h"


class CCommandReprLibrary
{
public:
    CCommandReprLibrary();

    ~CCommandReprLibrary();

    bool registerBlock(CCommandRepr* blockRepr);

    CCommandRepr* getBlockReprInstance(QString id) const;


    QStringList createCategoryList();

    bool contains(QString id);

    QList<CCommandRepr*> getBlocksOfCategory(QString cat);


    CCommandRepr* get(QString id) const;


private:
    QList<CCommandRepr*> m_listBlockReprs;

};

#endif // CCOMMANDREPRLIBRARY_H
