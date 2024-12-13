#include "CCommandBtnLibrary.h"

CCommandBtnLibrary::CCommandBtnLibrary() {}

CCommandBtnLibrary::~CCommandBtnLibrary()
{

}

bool CCommandBtnLibrary::registerBlock(CCommandBtn *blockRepr)
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

//调用命令块的拷贝构造，只有在读取历史生成过的命令区需要，新建命令块不需要
CCommandBtn *CCommandBtnLibrary::getBlockReprInstance(QString id) const
{
    CCommandBtn* block = get(id);


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

    foreach (CCommandBtn* blockRepr, m_listBlockReprs) {
        QStringList s = blockRepr->getId().split("_");
        list.append(s.first());
    }

    list.removeDuplicates();
    list.sort();

    return list;
}

bool CCommandBtnLibrary::contains(QString id)
{
    foreach (CCommandBtn* blockrepr, m_listBlockReprs) {
        if (blockrepr->getId() == id)
            return true;
    }

    return false;
}

QList<CCommandBtn *> CCommandBtnLibrary::getBlocksOfCategory(QString cat)
{
    QList<CCommandBtn*> list;

    foreach (CCommandBtn* blockRepr, m_listBlockReprs) {
        QStringList s = blockRepr->getId().split("_");
        if (s.first() == cat)
            list.append(blockRepr);
    }

    return list;
}

CCommandBtn *CCommandBtnLibrary::get(QString id) const
{
    foreach (CCommandBtn* blockrepr, m_listBlockReprs) {
        if (blockrepr->getId() == id)
            return blockrepr;
    }

    return NULL;
}
