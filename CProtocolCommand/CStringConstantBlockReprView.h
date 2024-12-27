#ifndef CSTRINGCONSTANTBLOCKREPRVIEW_H
#define CSTRINGCONSTANTBLOCKREPRVIEW_H

#include <QLineEdit>
#include <QGraphicsProxyWidget>
#include <QDoubleValidator>
#include "CCommandReprView.h"

class CConstantCommandBtn;

class CStringConstantBlockReprView : public CCommandReprView
{
    Q_OBJECT
public:
    CStringConstantBlockReprView();

    CStringConstantBlockReprView(CConstantCommandBtn* blockRepr, QGraphicsItem *parent = 0);

public slots:

    void stringChanged();

private:
    CConstantCommandBtn* _constantBlockRepr;
    QLineEdit* _lineEdit;
    QGraphicsProxyWidget* _proxy;
};

#endif // CSTRINGCONSTANTBLOCKREPRVIEW_H
