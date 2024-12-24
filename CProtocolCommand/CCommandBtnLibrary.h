#ifndef CCOMMANDBTNLIBRARY_H
#define CCOMMANDBTNLIBRARY_H

#include <QList>
#include <QStringList>
#include "CCommandRepr.h"


class CCommandBtnLibrary
{
public:
    CCommandBtnLibrary();

    ~CCommandBtnLibrary();

    bool registerBlock(CCommandRepr* blockRepr);

    CCommandRepr* getBlockReprInstance(QString id) const;


    QStringList createCategoryList();

    bool contains(QString id);

    QList<CCommandRepr*> getBlocksOfCategory(QString cat);


    CCommandRepr* get(QString id) const;


private:
    QList<CCommandRepr*> m_listBlockReprs;

};

#endif // CCOMMANDBTNLIBRARY_H
