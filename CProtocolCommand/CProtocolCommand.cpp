#include "CProtocolCommand.h"
#include "ui_CProtocolCommand.h"
#include <QPushButton>
#include <QGraphicsLinearLayout>
#include <QGraphicsGridLayout>
#include <QColorDialog>
#include <QPalette>
#include <QDebug>
#include "CCommandReprView.h"

CProtocolCommand::CProtocolCommand(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CProtocolCommand)
{
    ui->setupUi(this);

    m_pBlockCanvas = new CCommandCanvas(this);
    m_excuteHandler = new CCommandExcuteHandler();
    ui->graphicsView_2->setScene(m_pBlockCanvas);

    QRectF initialRect(0, 0, 720, 550); // 设置初始矩形大小为500x500

    //重要：画布固定大小才能固定坐标系
    m_pBlockCanvas->setSceneRect(initialRect);


    QGraphicsScene* scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    m_VarScene = new QGraphicsScene(this);
    ui->graphicsView_3->setScene(m_VarScene);


    // 初始化按钮信息数组
    buttonInfos[0] = {"if", 32,0};
    buttonInfos[1] = {"else", 32, 50};
    buttonInfos[2] = {"while", 100, 0};
    buttonInfos[3] = {"if_else", 100, 50};

    buttonInfos[4] = {"+", 32, 100};
    buttonInfos[5] = {"-", 32, 150};
    buttonInfos[6] = {"*", 100, 100};
    buttonInfos[7] = {"/", 32, 200};
    buttonInfos[8] = {"=", 100, 150};

    buttonInfos[9]  = {">", 100, 200};
    buttonInfos[10] = {"<", 32, 250};
    buttonInfos[11] = {"value", 100, 250};
    buttonInfos[12] = {"set_color", 32, 300};

    for (const auto& info : buttonInfos) {
        CCommandBtn* commandBtn = new CCommandBtn(info.text,info.text);
        commandBtn->setFixedSize(65, 45);
        commandBtn->setStyleSheet("color: black;");
        QGraphicsProxyWidget* proxy = scene ->addWidget(commandBtn);

        proxy->setPos(info.x,info.y);

        // 使用lambda表达式来连接按钮点击信号和自定义的槽函数逻辑，打印按钮文字
        connect(commandBtn, &CCommandBtn::sigClicked, this, &CProtocolCommand::onCommandBtnClicked);
    }

    m_pCommandBtnLibrary = m_CommandLibrary.createBlockReprLibrary();

    initialize();
    //createSprite();

    // if(m_Sprite)
    // {
    //     m_pBlockCanvas->setBackgroundBrush(QBrush(m_Sprite->getBlockSceneBackgroundColor()));
    // }
}

CProtocolCommand::~CProtocolCommand()
{
    qDeleteAll(m_listCommands);
    qDeleteAll(m_listVars);
    qDeleteAll(m_listSprites);
    // if(m_excuteHandler)
    // {
    //     delete m_excuteHandler;
    //     m_excuteHandler = nullptr;
    // }
    if(m_pCommandBtnLibrary)
    {
        delete m_pCommandBtnLibrary;
        m_pCommandBtnLibrary = nullptr;
    }
    if(m_Sprite)
    {
        delete m_Sprite;
        m_Sprite = nullptr;
    }
    if(m_pBlockCanvas)
    {
        delete m_pBlockCanvas;
        m_pBlockCanvas = nullptr;
    }
    delete ui;
}

void CProtocolCommand::initialize()
{
    CCommandRepr* eventCommandBtn = m_pCommandBtnLibrary->getBlockReprInstance("Start");
    if(eventCommandBtn != nullptr)
    {
        m_listCommands.append(eventCommandBtn);
    }

    connect(m_excuteHandler, &CCommandExcuteHandler::sigDrawingTicked, this, &CProtocolCommand::onTickReceived);
}

void CProtocolCommand::addCommand(CCommandRepr *commandBtn)
{
    if(commandBtn != nullptr)
    {
        m_listCommands.append(commandBtn);
        commandBtn->setHolderParent(this);
        m_pBlockCanvas->buildList();

        if( m_listCommands.first()->getReturnType() == CCommand::EVENT)
        {
            if(m_listCommands.first()->getNextStatement() == nullptr && commandBtn->getReturnType() == CCommand::VOID)
            {
                qDebug()<<u8"添加的首个物块是   "<< commandBtn->getId();
                m_listCommands.first()->placeNextStatement(commandBtn);
            }
        }
    }
}

bool CProtocolCommand::removeCommand(CCommandRepr *commandBtn)
{
    for(int i = 0; i < m_listCommands.size(); i++) {
        if(m_listCommands[i] == commandBtn) {
            m_listCommands.removeAt(i);
            m_pBlockCanvas->buildList();
            return true;
        }
    }
    return false;
}

void CProtocolCommand::createSprite()
{
    m_GlobalVars = new SimpleVarTable;
    //模拟一个控制的对象
    m_Sprite = new CSprite(m_GlobalVars);

    m_Sprite->setExecutionHandler(m_excuteHandler);


    QString strVarName = "test";

    //addVariable(new CVarCommandBtn(CCommand::NUMBER_VAR,strVarName));


    if(m_Sprite)
    {
        qDebug()<<"rrrrrrrr11111";
        compileSprite(m_Sprite);
    }
}

void CProtocolCommand::compileSprite(CSprite *sprite)
{
    foreach (CCommandRepr* blockRepr, m_listCommands) {
        //ignore non-event blocks
        if(blockRepr->getReturnType() == CCommand::EVENT) {
            qDebug()<<u8"有命令块";
            sprite->addBlock(compileEventBlock(blockRepr));
        }
        else
        {
            qDebug()<<u8"没有命令块";
        }
    }


    //增加变量
    foreach (CVarCommandBtn* varBlockRepr, m_listVars) {

        if(isListVar(varBlockRepr))
        {
            sprite->getVarTable()->addList(new SimpleValueList(varBlockRepr->getVarName(), getDataType(varBlockRepr)));
        }

        else
        {
            CVarIable* aa  = new SimpleVariable(varBlockRepr->getVarName(), getDataType(varBlockRepr));
            if(aa != nullptr)
            {
                sprite->getVarTable()->addVariable(aa);
            }
        }
    }
}

CEventCommand *CProtocolCommand::compileEventBlock(CCommandRepr *blockRepr)
{
    CEventCommand* block = (CEventCommand*)m_CommandLibrary.getBlockInstance(blockRepr->getId());   //这个id是指这个物块的名字，比如空格还是回车之类的
    if(block == NULL) {

        return NULL;
    }

    //重要:这里的关键是找到下一个物块，下一个物块是通过拖拽的时候确定的
    block->setStatement(compileBody(blockRepr->getNextStatement()));

    return block;
}

CStatementCommand* CProtocolCommand::compileBody(CCommandRepr *blockRepr)
{
    CStatementsCommand* statements = new CStatementsCommand();

    int i = 0;
    if(blockRepr == nullptr)
    {
        return statements;
    }

    do {
        statements->addStatement(compileStatement(blockRepr));
        blockRepr = blockRepr->getNextStatement();
        i ++ ;
    } while(blockRepr != NULL);

    qDebug() << u8"一共多少语句块" << i;
    return statements;
}

CStatementCommand* CProtocolCommand::compileStatement(CCommandRepr *blockRepr)
{

    if(blockRepr == nullptr)
    {
        return nullptr;
    }

    CStatementCommand* statement = (CStatementCommand*) m_CommandLibrary.getBlockInstance(blockRepr->getId());

    if(statement == nullptr) {

        return NULL;
    }

    //给具体的块增加参数，比如小于判断的左右两边框子的值,如果是while也是条件的值就是参数
    for(int i = 0; i < blockRepr->getNumParams(); i++) {
        statement->addParameter(compileParam(blockRepr->getParam(i)), i);
    }

    for(int i = 0; i < blockRepr->getNumBodies(); i++) {
        statement->addBody(compileBody(blockRepr->getBody(i)), i);
    }

    return statement;
}

CCommand *CProtocolCommand::compileParam(CCommandRepr *blockRepr)
{
    if(blockRepr == nullptr)
    {
        return nullptr;
    }

    if(CCommand::isExpressionParam(blockRepr->getReturnType()))
    {
        return compileExpression(blockRepr);
    }

    //添加了变量
    if(CCommand::isVariableParam(blockRepr->getReturnType()))
    {
        return compileVarBlock(blockRepr);
    }

    if(CCommand::isListParam(blockRepr->getReturnType()))
    {

    }
    return nullptr;
}

void CProtocolCommand::addVariable(CVarCommandBtn *var)
{
    m_listVars.append(var);
    m_VarScene->clear();

    QPoint pos(0, 0);
    foreach (CVarCommandBtn* var, m_listVars) {
        CCommandReprView* brv = CCommandReprView::newBlockReprView(var);
        brv->setPos(pos);
        m_VarScene->addItem(brv);
        pos += QPoint(0, var->getTotalSize().height() + 15);
    }

    m_VarScene->setSceneRect(-10, -10, m_VarScene->itemsBoundingRect().toRect().size().width(), m_VarScene->itemsBoundingRect().toRect().size().height());

}

void CProtocolCommand::removeVariable(CVarCommandBtn *var)
{
    m_listVars.removeAll(var);
}

bool CProtocolCommand::isListVar(CVarCommandBtn *varBlockRepr)
{
    CCommand::ParamType rtrn = varBlockRepr->getReturnType();

    return (rtrn == CCommand::BOOLEAN_LIST || rtrn == CCommand::NUMBER_LIST || rtrn == CCommand::STRING_LIST);
}

CValue::DataType CProtocolCommand::getDataType(CCommandRepr *blockRepr)
{
    CValue::DataType dataType = CValue::BOOLEAN;

    if(blockRepr->getReturnType() == CCommand::STRING_EXPRESSION || blockRepr->getReturnType() == CCommand::STRING_LIST || blockRepr->getReturnType() == CCommand::STRING_VAR)
    {
        dataType = CValue::STRING;
    }

    else if(blockRepr->getReturnType() == CCommand::NUMBER_EXPRESSION || blockRepr->getReturnType() == CCommand::NUMBER_LIST || blockRepr->getReturnType() == CCommand::NUMBER_VAR)
    {
        dataType = CValue::NUMBER;
    }
    return dataType;
}

CExpressionCommand *CProtocolCommand::compileExpression(CCommandRepr *blockRepr)
{
    if(blockRepr == nullptr)
    {
        return nullptr;
    }

    CExpressionCommand* expression = (CExpressionCommand*)m_CommandLibrary.getBlockInstance(blockRepr->getId());

    if(expression == NULL) //if constant or variable
    {
        return compileSpecialCaseExpression(blockRepr);
    }


    for(int i = 0; i < blockRepr->getNumParams(); i++) {
        expression->addParameter(compileParam(blockRepr->getParam(i)), i);
    }

    return expression;

}

CExpressionCommand *CProtocolCommand::compileSpecialCaseExpression(CCommandRepr *blockRepr)
{
    qDebug()<<u8"<<<<<<<<<<<     compileSpecialCaseExpression";
    if(blockRepr == NULL)
        return NULL;

    //if constant:

    //true or false
    if(blockRepr->getId() == "Boolean_true")
    {

    }

    if(blockRepr->getId() == "Boolean_false")
    {

    }

    //number or string
    if(blockRepr->isConstantBlockRepr()) {
        if(blockRepr->getReturnType() == CCommand::STRING_EXPRESSION)
        {
            return new CConstantCommand(new StringValue(((CConstantCommandBtn*)blockRepr)->getValue().toString()));
        }

        if(blockRepr->getReturnType() == CCommand::NUMBER_EXPRESSION)
        {
            return new CConstantCommand(new NumberValue(((CConstantCommandBtn*)blockRepr)->getValue().toDouble()));
        }
    }

    //if variable:
    if(blockRepr->isVarBlockRepr())
    {
        return compileVarBlock(blockRepr);
    }


    //if everything fails:

    return NULL;
}

CVarCommand *CProtocolCommand::compileVarBlock(CCommandRepr *blockRepr)
{
    CValue::DataType dataType = CValue::BOOLEAN;

    if(blockRepr->getReturnType() == CCommand::STRING_VAR || blockRepr->getReturnType() == CCommand::STRING_EXPRESSION)
    {
        dataType = CValue::STRING;
    }
    else if(blockRepr->getReturnType() == CCommand::NUMBER_VAR || blockRepr->getReturnType() == CCommand::NUMBER_EXPRESSION)
    {
        dataType = CValue::NUMBER;
    }
    return new CVarCommand(((CVarCommandBtn*)blockRepr)->getVarName(), dataType);
}

void CProtocolCommand::onTickReceived()
{
    if(m_bWorking)
    {
        return;
    }
    m_bWorking = true;
    if(m_Sprite)
    {
        qDebug()<<"sfafafa" << m_Sprite->getBlockSceneBackgroundColor();
        m_pBlockCanvas->setBackgroundBrush(QBrush(m_Sprite->getBlockSceneBackgroundColor()));
    }
    m_bWorking = false;
}

void CProtocolCommand::onCommandBtnClicked(QString strCat)
{
    CCommandRepr* clickedButton = nullptr;
    if(strCat == "value")
    {
        clickedButton = new CConstantCommandBtn(CCommand::NUMBER_EXPRESSION,false);
    }
    else
    {
        clickedButton = m_pCommandBtnLibrary->getBlockReprInstance(strCat);
        clickedButton->setLock(false);
    }

    if(clickedButton != nullptr)
    {
        clickedButton->setPosition(QPoint(x,y));
        addCommand(clickedButton);
    }

    if(m_listCommands.size())
    {
        if( y + 80 <= 500)
        {
            y += 80;
        }
        else
        {
            y = 20;

            x += 80;
        }
    }
}

void CProtocolCommand::onCommandBtnClicked1(QString strCat)
{
    m_lastID = strCat;
}

void CProtocolCommand::on_btn_Start_clicked()
{
    createSprite();
    //编译项目


    //开始运行
    m_excuteHandler->start();

    //默认触发事件是start之后

    if(m_Sprite != nullptr)
    {
        m_Sprite->sendSignal(CSignal(CSignal::START));
    }
}


void CProtocolCommand::on_pushButton_Nunber_clicked()
{

    QString strVarName = "num_" + QString::number(m_listVars.size());
    addVariable(new CVarCommandBtn(CCommand::NUMBER_VAR,strVarName,true));

}


void CProtocolCommand::on_pushButton_Text_clicked()
{

}


void CProtocolCommand::on_pushButton_Boolean_clicked()
{

}

void CProtocolCommand::on_pushButton_Color_clicked()
{

    QColor color = QColorDialog::getColor(Qt::white, nullptr);
    if (color.isValid()) {
        // 获取选择颜色的RGB分量
        int red = color.red();
        int green = color.green();
        int blue = color.blue();

        QString rgbStr = QString("%1,%2,%3").arg(red).arg(green).arg(blue);

        // 设置按钮的背景颜色为选择的颜色
        QPalette palette = ui->pushButton_Color->palette();
        palette.setColor(QPalette::Button, color);
        ui->pushButton_Color->setPalette(palette);

        CConstantCommandBtn* colorCommand = new CConstantCommandBtn(CCommand::STRING_EXPRESSION);
        if(colorCommand != nullptr)
        {
            colorCommand->setValue(rgbStr);
            colorCommand->setPosition(QPoint(x,y));
            addCommand(colorCommand);
        }

        if(m_listCommands.size())
        {
            if( y + 80 <= 500)
            {
                y += 80;
            }
            else
            {
                y = 20;

                x += 80;
            }
        }

    }
}

