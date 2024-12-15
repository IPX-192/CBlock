#ifndef CPROTOCOLCOMMAND_H
#define CPROTOCOLCOMMAND_H

#include <QWidget>
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>
#include <QPushButton>
#include <QList>
#include <QGraphicsView>
#include <QTimer>
#include "CCommandExcuteHandler.h"
#include "CSignal.h"
#include "CCommandBtn.h"
#include "CCommandLibrary.h"
#include "CCommandBtnLibrary.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class CProtocolCommand;
}
QT_END_NAMESPACE

// 定义按钮相关的文本和位置信息的结构体数组
struct ButtonInfo {
    const char* text;
    int x;
    int y;
    bool bAdd = false;
};

//定义要控制的类型
class TestA
{

};

class CProtocolCommand : public QWidget
{
    Q_OBJECT

public:
    CProtocolCommand(QWidget *parent = nullptr);
    ~CProtocolCommand();

    //复位命令设置区
    void resetCommandsList();

    void buildCommandsList();

    void addCommand(CCommandBtn* commandBtn);

    void removeCommand(CCommandBtn* commandBtn);

    void compileProject();

    void comileBody();

signals:
    //命令区变更
    void sigCommandsUpdated();

    void sigSendSignal(const CSignal &signal);

private slots:
    void onCommandsUpdated();

    //void onCommandBtnClicked();


    void onCommandBtnClicked(QString strCat);

    void onCommandBtnClicked1(QString strCat);

    //开始按钮

    void executionTick();


    void on_btn_Start_clicked();

    void on_pushButton_Nunber_clicked();

    void on_pushButton_Text_clicked();

    void on_pushButton_Boolean_clicked();

private:
    Ui::CProtocolCommand *ui;


    ButtonInfo buttonInfos[10];  // 作为成员变量定义按钮信息数组

    QList<CCommandBtn*> m_lisCommands;


    QList<QPushButton*> m_test;

    int m_iIndex;


    QGraphicsScene* m_CommandMainScene{nullptr};

    CCommandExcuteHandler m_excuteHandler;

    CCommandLibrary m_CommandLibrary;

    CCommandBtnLibrary* m_pCommandBtnLibrary{nullptr};

    CCommandBtn *m_curCommandBtn{nullptr};


    //控制的变量区

    int m_iValue{0};
    QString m_strValue{""};
    bool m_bValue{false};

};
#endif // CPROTOCOLCOMMAND_H
