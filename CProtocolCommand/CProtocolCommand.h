#ifndef CPROTOCOLCOMMAND_H
#define CPROTOCOLCOMMAND_H

#include <QWidget>
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>
#include <QPushButton>
#include <QList>
#include <QGraphicsView>
#include <QTimer>

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
// struct
// {

// };

class CProtocolCommand : public QWidget
{
    Q_OBJECT

public:
    CProtocolCommand(QWidget *parent = nullptr);
    ~CProtocolCommand();

    //复位命令设置区
    void resetCommandsList();

    void buildCommandsList();

    void addCommand(QPushButton* commandBtn);

    void removeCommand(QPushButton* commandBtn);

    void compileProject();

signals:
    //命令区变更
    void sigCommandsUpdated();

private slots:
    void onCommandsUpdated();

    void onCommandBtnClicked();

    //开始按钮

    void executionTick();


    void on_btn_Start_clicked();

private:
    Ui::CProtocolCommand *ui;


    ButtonInfo buttonInfos[12];  // 作为成员变量定义按钮信息数组

    QList<QPushButton*> m_lisCommands;


    QList<QPushButton*> m_test;


    QGraphicsScene* m_CommandMainScene{nullptr};

    QTimer* m_Timer;



    //控制的变量区

    int m_showValue{0};
};
#endif // CPROTOCOLCOMMAND_H
