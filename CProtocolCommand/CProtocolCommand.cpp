#include "CProtocolCommand.h"
#include "ui_CProtocolCommand.h"
#include <QPushButton>
#include <QGraphicsLinearLayout>
#include <QGraphicsGridLayout>
#include <QDebug>
#include "CCommandReprView.h"

CProtocolCommand::CProtocolCommand(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CProtocolCommand)
{
    ui->setupUi(this);

    m_pBlockCanvas = new CCommandCanvas(this);
    m_CommandMainScene = new QGraphicsScene();

    m_excuteHandler = new CCommandExcuteHandler();
    ui->graphicsView_2->setScene(m_pBlockCanvas);


    QGraphicsScene* scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);


    QGraphicsWidget *widget = new QGraphicsWidget;
    //QGraphicsGridLayout *layout = new QGraphicsGridLayout(widget);


    // 将 QGraphicsWidget 添加到场景中
    //scene->addItem(widget);


    // 初始化按钮信息数组
    buttonInfos[0] = {"if", 32,0};
    buttonInfos[1] = {"else", 32, 50};
    buttonInfos[2] = {"while", 100, 0};
    buttonInfos[3] = {"for", 100, 50};

    buttonInfos[4] = {"+", 32, 100};
    buttonInfos[5] = {"-", 32, 150};
    buttonInfos[6] = {"=", 100, 100};

    buttonInfos[7] = {">", 32, 200};
    buttonInfos[8] = {"<", 100, 150};
    buttonInfos[9] = {"Number_Number", 100, 200};

    int row = 0;
    int col = 0;

    int i = 0;
    //widget->setPos(0, 0);
    for (const auto& info : buttonInfos) {


        CCommandBtn* commandBtn = new CCommandBtn(info.text,info.text);
        commandBtn->setFixedSize(65, 45);
        commandBtn->setStyleSheet("color: black;");
        QGraphicsProxyWidget* proxy = scene ->addWidget(commandBtn);

        proxy->setPos(info.x,info.y);
        //layout->addItem(proxy,row,col); // 添加子部件
        qDebug() << "Setting position: " << info.x << info.y;

        // 更新行列索引
        col++;
        if (col >= 2) {
            col = 0;
            row++;
        }

        // 使用lambda表达式来连接按钮点击信号和自定义的槽函数逻辑，打印按钮文字
        connect(commandBtn, &CCommandBtn::sigClicked, this, &CProtocolCommand::onCommandBtnClicked);
    }

    //layout->setSpacing(30);
    //widget->setLayout(layout);


    m_pCommandBtnLibrary = m_CommandLibrary.createBlockReprLibrary();

    initialize();

}

CProtocolCommand::~CProtocolCommand()
{
    delete ui;
}

void CProtocolCommand::initialize()
{
    //CCommandBtn* eventCommandBtn = m_pCommandBtnLibrary->getBlockReprInstance("Start");
    //m_listCommands.append(eventCommandBtn);
}

void CProtocolCommand::addCommand(CCommandRepr *commandBtn)
{

    qDebug()<<"asffffffff "<<m_listCommands.size();
    if(commandBtn != nullptr)
    {
        m_listCommands.append(commandBtn);
        commandBtn->setHolderParent(this);
        m_pBlockCanvas->buildList();
    }

    // if (commandBtn != nullptr && !m_listCommands.contains(commandBtn)) {

    //     // connect(commandBtn, &CCommandBtn::sigClicked, this, &CProtocolCommand::onCommandBtnClicked1);

    //     m_listCommands.append(commandBtn);

    //     int x = 0;
    //     int y = m_listCommands.size() * 50;
    //     QGraphicsProxyWidget* proxy = m_CommandMainScene->addWidget(commandBtn);
    //     proxy->setPos(x, y);

    //     connect(commandBtn, &CCommandBtn::sigClicked, this, &CProtocolCommand::onCommandBtnClicked1);
    //     //emit onCommandsUpdated();
    // }
}

void CProtocolCommand::removeCommand(CCommandRepr *commandBtn)
{
    for(int i = 0; i < m_listCommands.size(); i++) {
        if(m_listCommands[i] == commandBtn) {
            m_listCommands.removeAt(i);
            m_pBlockCanvas->buildList();
        }
    }
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
    // foreach (CCommandBtn* blockRepr, m_listCommands) {
    //     //ignore non-event blocks
    //     if(blockRepr->getReturnType() == CCommand::EVENT) {
    //         qDebug()<<u8"有命令块";
    //         sprite->addBlock(compileEventBlock(blockRepr));
    //     }
    //     else
    //     {
    //         qDebug()<<u8"没有命令块";
    //     }
    // }


    // //增加变量
    // foreach (CVarCommandBtn* varBlockRepr, m_listVars) {

    //     if(isListVar(varBlockRepr))
    //     {
    //         sprite->getVarTable()->addList(new SimpleValueList(varBlockRepr->getVarName(), getDataType(varBlockRepr)));
    //     }

    //     else
    //     {
    //         CVarIable* aa  = new SimpleVariable(varBlockRepr->getVarName(), getDataType(varBlockRepr));
    //         if(aa != nullptr)
    //         {
    //             sprite->getVarTable()->addVariable(aa);
    //         }
    //     }
    // }
}

CEventCommand *CProtocolCommand::compileEventBlock(CCommandBtn *blockRepr)
{
    CEventCommand* block = (CEventCommand*)m_CommandLibrary.getBlockInstance(blockRepr->getId());   //这个id是指这个物块的名字，比如空格还是回车之类的
    if(block == NULL) {

        return NULL;
    }

    //重要:这里的关键是找到下一个物块，下一个物块是通过拖拽的时候确定的
    block->setStatement(compileBody(blockRepr->getNextStatement()));

    return block;
}

CStatementCommand* CProtocolCommand::compileBody(CCommandBtn *blockRepr)
{
    CStatementsCommand* statements = new CStatementsCommand();

    int i = 0;
    if(blockRepr == nullptr)
    {
        qDebug()<<"vvvvvvvvvvvvvvvvvvvvvvvv12";
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

CStatementCommand* CProtocolCommand::compileStatement(CCommandBtn *blockRepr)
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

CCommand *CProtocolCommand::compileParam(CCommandBtn *blockRepr)
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

    // var->setFixedSize(30, 30);
    // var->setStyleSheet("color: black;");
    // var->setText(var->getVarName());
    // addCommand(var);

    // m_listVars.append(var);

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

CValue::DataType CProtocolCommand::getDataType(CCommandBtn *blockRepr)
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

CExpressionCommand *CProtocolCommand::compileExpression(CCommandBtn *blockRepr)
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

CExpressionCommand *CProtocolCommand::compileSpecialCaseExpression(CCommandBtn *blockRepr)
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

CVarCommand *CProtocolCommand::compileVarBlock(CCommandBtn *blockRepr)
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

void CProtocolCommand::onCommandBtnClicked(QString strCat)
{

    // CCommandBtn* clickedButton = m_pCommandBtnLibrary->getBlockReprInstance(strCat);

    // if(clickedButton == nullptr)
    // {
    //     return;
    // }

    // clickedButton->setFixedSize(100, 45);
    // clickedButton->setStyleSheet("color: black;");
    // clickedButton->setText(strCat);
    // clickedButton->setLacked(true);


    // if( m_listCommands.size() > 0 &&  m_listCommands.first()->getId() == "Start")
    // {

    //     m_listCommands.first()->placeNextStatement(clickedButton);
    // }

    // else
    // {
    //     qDebug()<<"vvsdsada";
    // }


    // //测试代码
    // if(strCat == ">")
    // {
    //     foreach(CCommandBtn* block, m_listCommands) {


    //         if(m_lastID == block->getId())
    //         {
    //             block->placeParam(clickedButton,0);
    //             qDebug()<<"rrrrrrrr"<<block->getId();
    //         }
    //     }


    //     CConstantCommandBtn * aa = new CConstantCommandBtn(CCommand::NUMBER_EXPRESSION);

    //     aa->setValue(28);

    //     //clickedButton->placeParam(aa->copy(),0);

    //     CConstantCommandBtn * bb = new CConstantCommandBtn(CCommand::NUMBER_EXPRESSION);


    //     bb->setValue(20);


    //     //clickedButton->placeParam(bb->copy(),1);

    //     qDebug()<<"rrrrrrrr"<<clickedButton->getId();

    //     // //添加参数
    //     // if(m_listVars.size())
    //     // {


    //     // }

    // }
    // addCommand(clickedButton);

    CCommandRepr* clickedButton = nullptr;
    if(strCat == "Number_Number")
    {
        qDebug()<<"gggggggggggggggggrrrr ";
        clickedButton = new CConstantCommandBtn(CCommand::NUMBER_EXPRESSION);
    }
    else
    {
        clickedButton = m_pCommandBtnLibrary->getBlockReprInstance(strCat);
    }



    CCommandReprView* brv = CCommandReprView::newBlockReprView(clickedButton);

    y+= 50;
    brv->setPos(0,y);

    m_pBlockCanvas->addItem(brv);   //开始循环绘制物块
}

void CProtocolCommand::onCommandBtnClicked1(QString strCat)
{
    m_lastID = strCat;
}



void CProtocolCommand::executionTick()
{
    qDebug()<<"asfasfasfasffffffff";
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

    // CCommandBtn* clickedButton = new CCommandBtn("num","num");

    // clickedButton->setFixedSize(30, 30);
    // clickedButton->setStyleSheet("color: black;");

    // addCommand(clickedButton);

    QString strVarName = "num";

    addVariable(new CVarCommandBtn(CCommand::NUMBER_VAR,strVarName));



}


void CProtocolCommand::on_pushButton_Text_clicked()
{

}


void CProtocolCommand::on_pushButton_Boolean_clicked()
{

}

