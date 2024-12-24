#include "CConstantCommandBtn.h"
#include <QGraphicsProxyWidget>
#include <QLineEdit>
#include <QDebug>


CConstantCommandBtn::CConstantCommandBtn(CCommand::ParamType returnType)
    : CCommandRepr(returnType), m_Value(0)
{
    if(returnType == CCommand::STRING_EXPRESSION)
    {
        m_Value.setValue(QString(tr("text")));
    }

}

CConstantCommandBtn::CConstantCommandBtn(const CConstantCommandBtn &block): CCommandRepr(block.getReturnType()), m_Value(block.getValue())
{

}



CCommandRepr *CConstantCommandBtn::copy()
{
    return new CConstantCommandBtn(*this);
}


QSize CConstantCommandBtn::getTotalSize()
{
    return getSize();
}

QSize CConstantCommandBtn::getSize()
{
    return getHeaderSize();
}

QSize CConstantCommandBtn::getHeaderSize()
{
    QFont font("Arial", 11);
    font.setPixelSize(11);
    QLineEdit* lineedit = new QLineEdit;
    lineedit->setText(m_Value.toString());
    lineedit->setFont(font);
    lineedit->resize(60, 17);
    lineedit->setContentsMargins(0,0,0,0);
    QGraphicsProxyWidget proxy;
    proxy.setWidget(lineedit);

    return QSize(proxy.boundingRect().size().toSize().width(), proxy.boundingRect().size().toSize().height() - 4) + QSize(MARGIN_HORIZONTAL * 4, MARGIN *2);
}
