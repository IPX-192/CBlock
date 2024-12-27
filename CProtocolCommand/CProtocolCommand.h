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
#include "CCommand.h"
#include "CCommandBtn.h"
#include "CCommandLibrary.h"
#include "CCommandBtnLibrary.h"
#include "CStatementsCommand.h"
#include "CStatementCommand.h"
#include "CExpressionCommand.h"
#include "CConstantCommand.h"
#include "CConstantCommandBtn.h"
#include "CVarCommandBtn.h"
#include "CVarCommand.h"
#include "CSprite.h"
#include "CCommandRepr.h"
#include "CCommandCanvas.h"


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

    void initialize();

    void addCommand(CCommandRepr* commandBtn);

    bool removeCommand(CCommandRepr* commandBtn);

    void createSprite();

    void compileSprite(CSprite* sprite);

    QList<CCommandRepr*> getBlocks() const {return m_listCommands;}

    CEventCommand* compileEventBlock(CCommandRepr* blockRepr);

    CStatementCommand* compileBody(CCommandRepr *blockRepr);

    CStatementCommand* compileStatement(CCommandRepr *blockRepr);

    CCommand* compileParam(CCommandRepr *blockRepr);

    void addVariable(CVarCommandBtn* var);

    void removeVariable(CVarCommandBtn* var);


    bool isListVar(CVarCommandBtn* varBlockRepr);

    CValue::DataType getDataType(CCommandRepr* blockRepr);


    //编译常量和变量的表达式
    CExpressionCommand* compileExpression(CCommandRepr* blockRepr);

    CExpressionCommand* compileSpecialCaseExpression(CCommandRepr* blockRepr);

    CVarCommand* compileVarBlock(CCommandRepr* blockRepr);


signals:
    //命令区变更
    void sigCommandsUpdated();

    void sigSendSignal(const CSignal &signal);

private slots:


    //void onCommandBtnClicked();

    void onTickReceived();

    void onCommandBtnClicked(QString strCat);

    void onCommandBtnClicked1(QString strCat);

    //开始按钮

    void on_btn_Start_clicked();

    void on_pushButton_Nunber_clicked();

    void on_pushButton_Text_clicked();

    void on_pushButton_Boolean_clicked();

    void on_pushButton_Color_clicked();

private:
    Ui::CProtocolCommand *ui;


    ButtonInfo buttonInfos[13];  // 作为成员变量定义按钮信息数组

    QList<CCommandRepr*> m_listCommands;

    QList<CVarCommandBtn*> m_listVars;   //这个应该放在具体的对象中

    QList<CSprite*> m_listSprites;       //这个是控制的那个对象

    int m_iIndex;

    QString m_lastID{""};

    CCommandExcuteHandler* m_excuteHandler{nullptr};

    CCommandLibrary m_CommandLibrary;

    CCommandBtnLibrary* m_pCommandBtnLibrary{nullptr};

    CCommandBtn *m_curCommandBtn{nullptr};


    CSprite*   m_Sprite{nullptr};

    CCommandCanvas* m_pBlockCanvas{nullptr};

    QGraphicsScene* m_VarScene{nullptr};

    bool m_bWorking{false};


    //控制的变量区

    int m_iValue{0};
    QString m_strValue{""};
    bool m_bValue{false};

    SimpleVarTable* m_GlobalVars;

    int x = 20;
    int y = 20;

};
#endif // CPROTOCOLCOMMAND_H
