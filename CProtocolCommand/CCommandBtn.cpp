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
        m_ReturnType= block->getReturnType();
        m_strListParamLabels = block->getParamDescription().split("%p");
        for (int i = 0; i < m_strListParamLabels.size(); ++i) {
            m_strListParamLabels.replace(i, m_strListParamLabels.at(i).trimmed());
        }
        m_strListBodyLabels = block->getBodiesDescription().split("%b", QString::SkipEmptyParts);
        for (int i = 0; i < m_strListBodyLabels.size(); ++i) {
            m_strListBodyLabels.replace(i, m_strListBodyLabels.at(i).trimmed());
        }

        foreach (CCommand::ParamType type, block->getParamTypes()) {
            m_listParams.append(new CCommandParam(type));
        }

        for (int i = 0; i < block->getNumBodies(); ++i) {
            m_listBodies.append(nullptr);
        }
        m_qstrCat = block->getId();

        qDebug()<<"fffffffffffffffffff "<<m_qstrCat;
    }
}

CCommandBtn::CCommandBtn(QString cat, QString text, QWidget *parent):
    QPushButton(text, parent), m_qstrCat(cat)
{

    m_qstrID = cat;
    connect(this, &CCommandBtn::clicked, this, &CCommandBtn::onBtnClicked);
}

CCommandBtn::CCommandBtn(const CCommandBtn &repr)
{
    m_qstrID = repr.getId();
    m_ReturnType= repr.getReturnType();
    m_strListParamLabels = repr.getParamDescriptions();
    m_strListBodyLabels = repr.getBodyDescriptions();

    for (int i = 0; i < repr.getNumParams(); ++i)
    {
        CCommandParam* p = new CCommandParam(repr.getParamType(i));
        if(repr.getParam(i) != nullptr) {
            CCommandBtn* newParam = repr.getParam(i)->copy();
            newParam->setParent(this);
            //p->setBlock(newParam);
        }
        m_listParams.append(p);
    }

    for (int i = 0; i < repr.getNumBodies(); ++i)
    {
        CCommandBtn* body = repr.getBody(i);

        if (body == nullptr)
        {
            m_listBodies.append(nullptr);
        }

        else
        {
            CCommandBtn* newBody = body->copy();
            newBody->setParent(this);
            m_listBodies.append(newBody);
        }
    }

    if (repr.m_NextCommandBtn != nullptr)
    {
        m_NextCommandBtn = repr.m_NextCommandBtn->copy();
        m_NextCommandBtn->setParent(this);
    }
    else
    {
        m_NextCommandBtn = nullptr;
    }


    m_qstrCat = repr.getId();

}

CCommandBtn::~CCommandBtn()
{

}

CCommandBtn *CCommandBtn::copy()
{
    return new CCommandBtn(*this);
}

bool CCommandBtn::removeBody(int index)
{
    return false;
}

bool CCommandBtn::removeParam(int index)
{
    return false;
}

bool CCommandBtn::removeNextStatement()
{
    return false;
}

bool CCommandBtn::removeFromParent()
{
    return false;
}

int CCommandBtn::getNumBodies() const
{
    return m_listBodies.size();
}

int CCommandBtn::getNumParams() const
{
    return m_listParams.size();
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

    //m_listParams.at(index)->setBlock(repr);

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
    m_listBodies.replace(index,repr);

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

bool CCommandBtn::needParam()
{
    return m_bNeedParam;
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

    //return m_listParams.at(index)->getBlock();
}

CCommand::ParamType CCommandBtn::getParamType(int index) const
{
    return m_listParams.at(index)->getParamType();
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

CCommandBtn::CCommandBtn(CCommand::ParamType type, QString name, bool isVar)
{

    if(isVar) {
        m_qstrID = QString("Var"); //used for creating variables
        m_strListParamLabels.append(name);
    } else {
        QString cat;
        if (type == CCommand::NUMBER_EXPRESSION)
            cat = "Number";
        else if (type == CCommand::BOOLEAN_EXPRESSION)
            cat = "Boolean";
        else
            cat = "String";
        m_qstrID = cat + QString("_") + name; //used for creating true and false

        if (name == "true")
            m_strListParamLabels.append(tr("true"));
        else
            m_strListParamLabels.append(tr("false"));
    }
    m_ReturnType = type;
}

CCommandBtn::CCommandBtn(CCommand::ParamType type)
{


    if(type == CCommand::STRING_EXPRESSION)
    {
        m_qstrID = "String_String";
    }

    else if (type == CCommand::NUMBER_EXPRESSION)
    {
        m_qstrID = "Number_Number";
    }

    else if (type == CCommand::SPRITE)
    {
        m_qstrID = "Sprite_Sprite";
    }

    else if (type == CCommand::FUNCTION_START)
    {
        m_qstrID = "Function_Start";
    }

    m_ReturnType = type;

    qDebug()<<"vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv" << m_qstrID;
}

void CCommandBtn::mousePressEvent(QMouseEvent *event)
{
    QPushButton::mousePressEvent(event);


    qDebug()<<"sfasfasfsafassssttttt22" << m_qstrID;
    // 切换选中状态
    m_checked =!m_checked;


    if(m_bLacked && m_checked)
    {
        emit sigClicked(m_qstrCat);
    }

    update();
}

void CCommandBtn::onBtnClicked()
{
    emit sigClicked(m_qstrCat);
}

void CCommandBtn::onBtnClicked1()
{
    qDebug()<<"sfasfasfsafassssttttt1";
}
