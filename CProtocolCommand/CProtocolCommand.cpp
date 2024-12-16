#include "CProtocolCommand.h"
#include "ui_CProtocolCommand.h"
#include <QPushButton>
#include <QGraphicsLinearLayout>
#include <QGraphicsGridLayout>
#include <QDebug>

CProtocolCommand::CProtocolCommand(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CProtocolCommand)
{
    ui->setupUi(this);


    m_CommandMainScene = new QGraphicsScene();
    ui->graphicsView_2->setScene(m_CommandMainScene);

    m_CommandMainScene->clear();
    connect(this,&CProtocolCommand::sigCommandsUpdated,this,&CProtocolCommand::onCommandsUpdated);


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
    buttonInfos[9] = {"+=", 100, 200};

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
}

CProtocolCommand::~CProtocolCommand()
{
    delete ui;
}

void CProtocolCommand::resetCommandsList()
{
    // 先删除所有 QGraphicsProxyWidget
    foreach (QGraphicsItem* item, m_CommandMainScene->items()) {
        QGraphicsProxyWidget* proxyWidget = qgraphicsitem_cast<QGraphicsProxyWidget*>(item);
        if (proxyWidget) {
            QWidget* widget = proxyWidget->widget();
            if (widget) {
                widget->setParent(nullptr);  // 确保 widget 的父对象不会影响到删除
            }
            delete proxyWidget;  // 删除 QGraphicsProxyWidget
        }
    }

    // 清理场景中的所有项
    m_CommandMainScene->clear();
}

void CProtocolCommand::buildCommandsList()
{

}

void CProtocolCommand::addCommand(CCommandBtn *commandBtn)
{
    if (commandBtn != nullptr && !m_lisCommands.contains(commandBtn)) {

        // connect(commandBtn, &CCommandBtn::sigClicked, this, &CProtocolCommand::onCommandBtnClicked1);

        m_lisCommands.append(commandBtn);

        int x = 0;
        int y = m_lisCommands.size() * 50;
        QGraphicsProxyWidget* proxy = m_CommandMainScene->addWidget(commandBtn);
        proxy->setPos(x, y);

        connect(commandBtn, &CCommandBtn::sigClicked, this, &CProtocolCommand::onCommandBtnClicked1);
        //emit onCommandsUpdated();
    }
}

void CProtocolCommand::removeCommand(CCommandBtn *commandBtn)
{
    for(int i = 0; i < m_lisCommands.size(); i++) {
        if(m_lisCommands[i] == commandBtn) {
            m_lisCommands.removeAt(i);
            emit onCommandsUpdated();
        }
    }
}

void CProtocolCommand::compileProject()
{
    //只要放入了命令块就开始编译
    if(m_lisCommands.size())
    {
        comileBody(m_lisCommands.first());
    }
}

CStatementCommand* CProtocolCommand::comileBody(CCommandBtn *blockRepr)
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
        statement->addBody(comileBody(blockRepr->getBody(i)), i);
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

    if(CCommand::isVariableParam(blockRepr->getReturnType()))
    {

    }

    if(CCommand::isListParam(blockRepr->getReturnType()))
    {

    }
    return nullptr;
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
        // return compileSpecialCaseExpression(blockRepr);
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

CVarCommandBtn *CProtocolCommand::compileVarBlock(CCommandBtn *blockRepr)
{
    // Value::DataType dataType = Value::BOOLEAN;

    // if(blockRepr->getReturnType() == Block::STRING_VAR || blockRepr->getReturnType() == Block::STRING_EXPRESSION)
    //     dataType = Value::STRING;

    // else if(blockRepr->getReturnType() == Block::NUMBER_VAR || blockRepr->getReturnType() == Block::NUMBER_EXPRESSION)
    //     dataType = Value::NUMBER;

    // return new VarBlock(((VarBlockRepr*)blockRepr)->getVarName(), dataType);
    return nullptr;
}


void CProtocolCommand::onCommandsUpdated()
{
    buildCommandsList();
}

void CProtocolCommand::onCommandBtnClicked(QString strCat)
{
    qDebug()<<"safasfsafase2" << strCat;

    CCommandBtn* clickedButton = new CCommandBtn(strCat,strCat);


    clickedButton->setFixedSize(65, 45);
    clickedButton->setStyleSheet("color: black;");
    clickedButton->setLacked(true);

    addCommand(clickedButton);

}

void CProtocolCommand::onCommandBtnClicked1(QString strCat)
{
    qDebug()<<"safasfsafase3" << strCat;

    //  foreach(CCommandBtn* block, m_lisCommands) {



    // qDebug()<<"fffffffff" << block->getId();


    //  }


}

// void CProtocolCommand::onCommandBtnClicked()
// {

//     CCommandBtn* clickedButton = qobject_cast<CCommandBtn*>(sender());

//     if (clickedButton) {
//         qDebug() << "Clicked button text: " << clickedButton->text();

//         addCommand(clickedButton);
//     }
// }

void CProtocolCommand::executionTick()
{
    qDebug()<<"asfasfasfasffffffff";
}

void CProtocolCommand::on_btn_Start_clicked()
{


    //编译项目
    compileProject();

    //开始运行
    m_excuteHandler.start();

    //默认触发事件是start之后
    emit sigSendSignal(CSignal(CSignal::START));


}


void CProtocolCommand::on_pushButton_Nunber_clicked()
{

    CCommandBtn* clickedButton = new CCommandBtn("number","number");


    clickedButton->setFixedSize(30, 30);
    clickedButton->setStyleSheet("color: black;");

    addCommand(clickedButton);

}


void CProtocolCommand::on_pushButton_Text_clicked()
{

}


void CProtocolCommand::on_pushButton_Boolean_clicked()
{

}

