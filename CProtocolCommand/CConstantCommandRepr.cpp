#include "CConstantCommandRepr.h"
#include <QGraphicsProxyWidget>
#include <QLineEdit>
#include <QDebug>


CConstantCommandRepr::CConstantCommandRepr(CCommand::ParamType returnType, bool locked)
    : CCommandRepr(returnType,locked), m_Value(0)
{
    if(returnType == CCommand::STRING_EXPRESSION)
    {
        m_Value.setValue(QString(tr("text")));
    }

}

CConstantCommandRepr::CConstantCommandRepr(const CConstantCommandRepr &block): CCommandRepr(block.getReturnType(), block.isLocked()), m_Value(block.getValue())
{

}

CCommandRepr *CConstantCommandRepr::copy()
{
    return new CConstantCommandRepr(*this);
}

void CConstantCommandRepr::setValue(QVariant value)
{
    m_Value = value;
    emitBlockUpdated(true, true, true);
}

QSize CConstantCommandRepr::getTotalSize()
{
    return getSize();
}

QSize CConstantCommandRepr::getSize()
{
    return getHeaderSize();
}

QSize CConstantCommandRepr::getHeaderSize()
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
