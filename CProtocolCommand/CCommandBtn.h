#ifndef CCOMMANDBTN_H
#define CCOMMANDBTN_H

#include <QPushButton>

#include <QStringList>
#include <QString>
#include <QPoint>
#include <QSize>
#include <QFont>
#include <QList>
#include <QDebug>
#include "CCommand.h"

class CCommandParam;
class CCommandBtn : public QPushButton
{
    Q_OBJECT
public:
    CCommandBtn(CCommand* block);

    explicit CCommandBtn(QString cat,QString text, QWidget *parent = 0);

    CCommandBtn(const CCommandBtn& repr);

    virtual ~CCommandBtn();

    virtual CCommandBtn* copy();

    QString getId() const { return m_qstrID; }


    bool placeParam(CCommandBtn* repr, int index);

    bool placeBody(CCommandBtn* repr, int index);


    bool placeNextStatement(CCommandBtn* repr);

    bool doesBodyFit(CCommandBtn* repr, int index);

    bool doesParamFit(CCommandBtn* repr, int index);

    CCommandBtn* getBody(int index) const;

    CCommandBtn* getParam(int index) const;

    CCommand::ParamType getReturnType() const { return m_ReturnType; };



signals:
         // void sigClicked(QString);

public slots:
    void onBtnClicked();

private:
    QString m_qstrID;
    QString m_qstrCat;

    CCommand::ParamType m_ReturnType;
    CCommandBtn* m_NextCommandBtn;

    QList<CCommandParam*> m_listParams;   //一个单独的块里面的参数

    QList<CCommandBtn*> m_listBodies;   //一个块里面的语句是一个单独的块
};



#endif // CCOMMANDBTN_H
