#include "CCommandBtn.h"
#include "CCommandParam.h"

CCommandBtn::CCommandBtn(CCommand *block)
{
    if(block)
    {
        m_qstrID = block->getId();
    }
}

CCommandBtn::CCommandBtn(QString cat, QString text, QWidget *parent):
    QPushButton(text, parent), m_qstrCat(cat)
{
    // connect(this, SIGNAL(sigClicked()), this, SLOT(onBtnClicked()));

    //  connect(this, &CCommandBtn::sigClicked, this, &CCommandBtn::onBtnClicked);

}

CCommandBtn::CCommandBtn(const CCommandBtn &repr)
{

}

CCommandBtn::~CCommandBtn()
{

}

CCommandBtn *CCommandBtn::copy()
{
    return new CCommandBtn(*this);
}

bool CCommandBtn::placeParam(CCommandBtn *repr, int index)
{
    if(repr == nullptr)
    {
        return false;
    }
    if(!doesParamFit(repr,index))
    {
        return false;
    }
    m_listBodies.replace(index,repr);
}

bool CCommandBtn::placeBody(CCommandBtn *repr, int index)
{
    if(repr == nullptr)
    {
        return false;
    }
    if(!doesBodyFit(repr,index))
    {
        return false;
    }
    m_listParams.at(index)->setBlock(repr);

}

bool CCommandBtn::placeNextStatement(CCommandBtn *repr)
{
    if(repr == nullptr)
    {
        return false;
    }
    if(!doesBodyFit(repr,-1))
    {
        return false;
    }
    m_NextCommandBtn = repr;
}

bool CCommandBtn::doesBodyFit(CCommandBtn *repr, int index)
{
    if(repr == nullptr)
    {
        return false;
    }
    return (repr->getReturnType() == CCommand::VOID);
}

bool CCommandBtn::doesParamFit(CCommandBtn *repr, int index)
{
    if(repr == nullptr)
    {
        return false;
    }

    CCommand::ParamType expected = m_listParams.at(index)->getParamType();
    CCommand::ParamType type = repr->getReturnType();

    if (expected == type)
    {
        return true;
    }

    if (expected == CCommand::NUMBER_EXPRESSION && type == CCommand::NUMBER_VAR)
    {
        return true;
    }

    if (expected == CCommand::BOOLEAN_EXPRESSION && type == CCommand::BOOLEAN_VAR)
    {
        return true;
    }

    if (expected == CCommand::STRING_EXPRESSION && type == CCommand::STRING_VAR)
    {
        return true;
    }
    return false;
}

CCommandBtn *CCommandBtn::getBody(int index) const
{
    if (index < 0 || index >= m_listBodies.size())
    {
        return nullptr;
    }

    return m_listBodies.at(index);
}

CCommandBtn *CCommandBtn::getParam(int index) const
{
    if (index < 0 || index >= m_listParams.size())
    {
        return nullptr;
    }

    return m_listParams.at(index)->getBlock();
}

void CCommandBtn::onBtnClicked()
{
    qDebug()<<"safasfsafase1" << m_qstrCat;
    //  emit sigClicked(m_qstrCat);
}
