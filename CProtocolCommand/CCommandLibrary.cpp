#include "CCommandLibrary.h"
#include "CCommandBtnLibrary.h"
#include "CCommand.h"

CCommandLibrary::CCommandLibrary() {

    registerBlock(new CIfCommandBtn());
    registerBlock(new CIfElseCommandBtn());
    registerBlock(new CWhileCommandBtn());
    registerBlock(new CGreaterThanNumberCommand());

}

CCommandLibrary::~CCommandLibrary()
{
    foreach (CCommand* block, m_listCommand) {
        if(block != NULL)
            delete block;
    }

    m_listCommand.clear();
}

bool CCommandLibrary::registerBlock(CCommand *block)
{
    if(block == nullptr)
    {
        return false;
    }
    if(contains(block->getId()))
    {
        return false;
    }
    m_listCommand.append(block);

}

CCommand *CCommandLibrary::getBlockInstance(QString id) const
{
    CCommand* block = get(id);


    if(block == nullptr)
    {
        return nullptr;
    }
    else
    {
        return block->newInstance();
    }

}

CCommandBtnLibrary* CCommandLibrary::createBlockReprLibrary() const
{
    CCommandBtnLibrary* lib = new CCommandBtnLibrary;

    foreach (CCommand* block, m_listCommand) {
        lib->registerBlock(new CCommandBtn(block));
    }

    return lib;
}

bool CCommandLibrary::contains(QString id)
{
    foreach (CCommand* block, m_listCommand) {
        if (block->getId() == id)
        {
            return true;
        }
    }

    return false;
}

CCommand *CCommandLibrary::get(QString id) const
{
    foreach (CCommand* block, m_listCommand) {
        if (block->getId() == id)
        {
            return block;
        }
    }

    return nullptr;
}
