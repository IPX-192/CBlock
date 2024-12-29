#include "CNumberConstantCommandBtnView.h"
#include "CConstantCommandRepr.h"

#include <QDebug>
#include <climits>

CNumberConstantCommandBtnView::CNumberConstantCommandBtnView(CConstantCommandRepr *blockRepr, QGraphicsItem *parent)
    :CCommandReprView(blockRepr, parent), _constantBlockRepr(blockRepr)
{
    QFont font("Arial", 11);
    font.setPixelSize(11);
    _lineEdit = new QLineEdit(QString::number(_constantBlockRepr->getValue().toDouble()));
    _lineEdit->setFont(font);
    _lineEdit->resize(60, 17);
    QPalette palette;
    palette.setBrush(QPalette::Background, Qt::transparent);
    _lineEdit->setPalette(palette);
    _lineEdit->setAutoFillBackground(false);
    _validator = new QDoubleValidator(INT_MIN, INT_MAX, 4, this);
    _validator->setNotation(QDoubleValidator::StandardNotation);
    _lineEdit->setValidator(_validator);
    _proxy = new QGraphicsProxyWidget;
    _proxy->setWidget(_lineEdit);
    _proxy->setPos(CCommandRepr::MARGIN_HORIZONTAL*2, CCommandRepr::MARGIN);
    _proxy->setParentItem(this);

    connect(_lineEdit, SIGNAL(textChanged(QString)), this, SLOT(numberChanged()));
}

void CNumberConstantCommandBtnView::numberChanged()
{
    _constantBlockRepr->setValue(QVariant(_lineEdit->text().toDouble()));
}
