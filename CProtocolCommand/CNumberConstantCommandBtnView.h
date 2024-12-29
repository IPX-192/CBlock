#ifndef CNUMBERCONSTANTCOMMANDBTNVIEW_H
#define CNUMBERCONSTANTCOMMANDBTNVIEW_H
#include <QLineEdit>
#include <QGraphicsProxyWidget>
#include <QDoubleValidator>
#include "CCommandReprView.h"

class CConstantCommandRepr;
class CNumberConstantCommandBtnView : public CCommandReprView
{
    Q_OBJECT
public:
    CNumberConstantCommandBtnView();

    CNumberConstantCommandBtnView(CConstantCommandRepr* blockRepr, QGraphicsItem *parent = 0);

public slots:
    /**
     * @brief This function is called when the text changes
     */
    void numberChanged();

private:
    CConstantCommandRepr* _constantBlockRepr;
    QLineEdit* _lineEdit;
    QGraphicsProxyWidget* _proxy;
    QDoubleValidator* _validator;

};



#endif // CNUMBERCONSTANTCOMMANDBTNVIEW_H
