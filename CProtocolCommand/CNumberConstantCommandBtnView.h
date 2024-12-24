#ifndef CNUMBERCONSTANTCOMMANDBTNVIEW_H
#define CNUMBERCONSTANTCOMMANDBTNVIEW_H
#include <QLineEdit>
#include <QGraphicsProxyWidget>
#include <QDoubleValidator>
#include "CCommandReprView.h"

class CConstantCommandBtn;
class CNumberConstantCommandBtnView : public CCommandReprView
{
    Q_OBJECT
public:
    CNumberConstantCommandBtnView();

    CNumberConstantCommandBtnView(CConstantCommandBtn* blockRepr, QGraphicsItem *parent = 0);

public slots:
    /**
     * @brief This function is called when the text changes
     */
    void numberChanged();

private:
    CConstantCommandBtn* _constantBlockRepr;
    QLineEdit* _lineEdit;
    QGraphicsProxyWidget* _proxy;
    QDoubleValidator* _validator;

};



#endif // CNUMBERCONSTANTCOMMANDBTNVIEW_H
