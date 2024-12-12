#ifndef CCOMMANDBTNLIBRARY_H
#define CCOMMANDBTNLIBRARY_H

#include <QList>
#include <QStringList>
#include "CCommandBtn.h"

class CCommandBtnLibrary
{
public:
    CCommandBtnLibrary();

    ~CCommandBtnLibrary();

    bool registerBlock(CCommandBtn* blockRepr);

    CCommandBtn* getBlockReprInstance(QString id) const;


    QStringList createCategoryList();

    bool contains(QString id);

    QList<CCommandBtn*> getBlocksOfCategory(QString cat);


    CCommandBtn* get(QString id) const;


private:
    QList<CCommandBtn*> m_listBlockReprs;

};

#endif // CCOMMANDBTNLIBRARY_H
