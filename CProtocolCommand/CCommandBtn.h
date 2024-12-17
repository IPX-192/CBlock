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

    CCommandBtn(QString cat,QString text, QWidget *parent = 0);

    CCommandBtn(const CCommandBtn& repr);

    virtual ~CCommandBtn();

    virtual CCommandBtn* copy();

    QString getId() const { return m_qstrID; }

    bool removeBody(int index);

    bool removeParam(int index);

    bool removeNextStatement();

    bool removeFromParent();

    int getNumBodies() const;

    int getNumParams() const;


    bool placeParam(CCommandBtn* repr, int index);

    bool placeBody(CCommandBtn* repr, int index);


    bool placeNextStatement(CCommandBtn* repr);

    bool doesBodyFit(CCommandBtn* repr, int index);

    bool doesParamFit(CCommandBtn* repr, int index);

    bool needParam();


    CCommandBtn* getBody(int index) const;

    CCommandBtn* getParam(int index) const;

    CCommandBtn* getNextStatement() { return m_NextCommandBtn; }

    CCommand::ParamType getReturnType() const { return m_ReturnType; };


    // 用于表示按钮是否被选中的属性
    bool isChecked() const;

    void setChecked(bool checked);

    void setLacked(bool lacked);

    virtual bool isConstantBlockRepr() const { return false; }

    virtual bool isVarBlockRepr() const { return false; }


protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

    CCommandBtn(CCommand::ParamType type, QString name, bool isVar = true);
    CCommandBtn(CCommand::ParamType type);


signals:
    void sigClicked(QString strCat);

public slots:
    void onBtnClicked();

    void onBtnClicked1();


private:
    QString m_qstrID;
    QString m_qstrCat;

    CCommand::ParamType m_ReturnType;

    QStringList m_strListParamLabels;

    QStringList m_strListBodyLabels;

    CCommandBtn* m_NextCommandBtn;

    bool m_checked{false};

    bool m_bLacked{false};

    bool m_bNeedParam{false};

    QList<CCommandParam*> m_listParams;   //一个单独的块里面的参数

    QList<CCommandBtn*> m_listBodies;   //一个块里面的语句是一个单独的块
};



#endif // CCOMMANDBTN_H
