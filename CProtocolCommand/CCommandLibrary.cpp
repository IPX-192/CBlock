#include "CCommandLibrary.h"
#include "CCommandBtnLibrary.h"
#include "CCommand.h"

CCommandLibrary::CCommandLibrary() {

    registerBlock(new CIfCommand());
    registerBlock(new CIfElseCommand());
    registerBlock(new CWhileCommand());
    registerBlock(new CDivideCommand());
    registerBlock(new CEqualNumberCommand());
    registerBlock(new CGreaterThanNumberCommand());
    registerBlock(new CLessThanNumberCommand());
    registerBlock(new CMinusCommand());
    registerBlock(new CMultiplyCommand());
    registerBlock(new CNumberRassignment());
    registerBlock(new CPlusCommand());
    registerBlock(new CStartCommand());
    registerBlock(new CBlockSceneBGColorCommand());
    registerBlock(new CElseCommand());

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
        lib->registerBlock(new CCommandRepr(block,true));
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
