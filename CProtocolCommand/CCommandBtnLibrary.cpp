#include "CCommandBtnLibrary.h"
#include "CConstantCommandBtn.h"

CCommandBtnLibrary::CCommandBtnLibrary() {

    registerBlock(new CConstantCommandBtn(CCommand::STRING_EXPRESSION));
    registerBlock(new CConstantCommandBtn(CCommand::NUMBER_EXPRESSION));
}

CCommandBtnLibrary::~CCommandBtnLibrary()
{

}

bool CCommandBtnLibrary::registerBlock(CCommandRepr *blockRepr)
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

CCommandRepr *CCommandBtnLibrary::getBlockReprInstance(QString id) const
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

QStringList CCommandBtnLibrary::createCategoryList()
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

bool CCommandBtnLibrary::contains(QString id)
{
    foreach (CCommandRepr* blockrepr, m_listBlockReprs) {
        if (blockrepr->getId() == id)
            return true;
    }

    return false;
}

QList<CCommandRepr *> CCommandBtnLibrary::getBlocksOfCategory(QString cat)
{
    QList<CCommandRepr*> list;

    foreach (CCommandRepr* blockRepr, m_listBlockReprs) {
        QStringList s = blockRepr->getId().split("_");
        if (s.first() == cat)
            list.append(blockRepr);
    }

    return list;
}

CCommandRepr *CCommandBtnLibrary::get(QString id) const
{
    foreach (CCommandRepr* blockrepr, m_listBlockReprs) {
        if (blockrepr->getId() == id)
            return blockrepr;
    }

    return NULL;
}
