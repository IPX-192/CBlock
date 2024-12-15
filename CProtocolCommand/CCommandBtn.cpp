#include "CCommandBtn.h"
#include "CCommandParam.h"
#include <QPushButton>
#include <QStyleOptionButton>
#include <QPainter>
#include <QMouseEvent>

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

    connect(this, &CCommandBtn::clicked, this, &CCommandBtn::onBtnClicked);

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

bool CCommandBtn::isChecked() const
{
    return m_checked;
}

void CCommandBtn::setChecked(bool checked)
{
    m_checked = checked;
    update();  // 重绘按钮，使样式更新显示
}

void CCommandBtn::setLacked(bool lacked)
{
    m_bLacked = lacked;
}

void CCommandBtn::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);
    QStyleOptionButton option;
    initStyleOption(&option);

    QPainter painter(this);
    if (m_checked && m_bLacked) {
        // 设置画笔为红色，宽度为2像素，绘制矩形边框来表示选中状态
        QPen pen(Qt::red);
        pen.setWidth(2);
        painter.setPen(pen);
        painter.drawRect(rect().adjusted(0, 0, -1, -1));
    }
}

// void CCommandBtn::mousePressEvent(QMouseEvent *event)
// {
//     QPushButton::mousePressEvent(event);
//     // 切换选中状态
//     m_checked =!m_checked;
//     update();
// }

void CCommandBtn::onBtnClicked()
{
    m_checked =!m_checked;
    if(m_checked)
    {
        emit sigClicked(m_qstrCat);
    }
    update();
}
