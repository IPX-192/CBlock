#include "CCommandReprLibrary.h"
#include "CConstantCommandRepr.h"

CCommandReprLibrary::CCommandReprLibrary() {

    registerBlock(new CConstantCommandRepr(CCommand::STRING_EXPRESSION));
    registerBlock(new CConstantCommandRepr(CCommand::NUMBER_EXPRESSION));
}

CCommandReprLibrary::~CCommandReprLibrary()
{

}

bool CCommandReprLibrary::registerBlock(CCommandRepr *blockRepr)
{
    if(blockRepr == nullptr)
    {
        return false;
    }

    if(contains(blockRepr->getId()))
    {
        return false;
    }
    m_listBlockReprs.append(blockRepr);
}

CCommandRepr *CCommandReprLibrary::getBlockReprInstance(QString id) const
{
    CCommandRepr* block = get(id);


    if(block == nullptr)
    {
        return nullptr;
    }
    else
    {
        return block->copy();
    }
}

QStringList CCommandReprLibrary::createCategoryList()
{
    QStringList list;

    foreach (CCommandRepr* blockRepr, m_listBlockReprs) {
        QStringList s = blockRepr->getId().split("_");
        list.append(s.first());
    }

    list.removeDuplicates();
    list.sort();

    return list;
}

bool CCommandReprLibrary::contains(QString id)
{
    foreach (CCommandRepr* blockrepr, m_listBlockReprs) {
        if (blockrepr->getId() == id)
            return true;
    }

    return false;
}

QList<CCommandRepr *> CCommandReprLibrary::getBlocksOfCategory(QString cat)
{
    QList<CCommandRepr*> list;

    foreach (CCommandRepr* blockRepr, m_listBlockReprs) {
        QStringList s = blockRepr->getId().split("_");
        if (s.first() == cat)
            list.append(blockRepr);
    }

    return list;
}

CCommandRepr *CCommandReprLibrary::get(QString id) const
{
    foreach (CCommandRepr* blockrepr, m_listBlockReprs) {
        if (blockrepr->getId() == id)
            return blockrepr;
    }

    return NULL;
}
