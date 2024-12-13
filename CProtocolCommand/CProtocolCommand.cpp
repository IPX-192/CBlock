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
    buttonInfos[9] = {"Add", 100, 200};

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
        connect(commandBtn, &CCommandBtn::clicked, this, &CProtocolCommand::onCommandBtnClicked);
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
    foreach (QPushButton* block, m_test) {

    }
    m_CommandMainScene->clear();

    m_test.clear();
}

void CProtocolCommand::buildCommandsList()
{
    resetCommandsList();

    foreach(QPushButton* block, m_lisCommands) {

        m_test.append(block);
        //blockView->setPos(block->getPosition());
        QGraphicsProxyWidget* proxy = m_CommandMainScene -> addWidget(block);
        proxy->setPos(50, 100);

        //  m_CommandMainScene->addItem((QGraphicsItem*)block);
    }
}

void CProtocolCommand::addCommand(CCommandBtn *commandBtn)
{
    if(commandBtn != NULL) {
        m_lisCommands.append(commandBtn);
        emit onCommandsUpdated();
    }

    //添加到中间区域
    QGraphicsProxyWidget* proxy = m_CommandMainScene ->addWidget(commandBtn);
    proxy->setPos(100,200);
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

    }
}

void CProtocolCommand::comileBody()
{

}

void CProtocolCommand::onCommandsUpdated()
{
    buildCommandsList();
}

void CProtocolCommand::onCommandBtnClicked()
{
    //qDebug()<<"safasfsafase2" << strCat;

    CCommandBtn* clickedButton = qobject_cast<CCommandBtn*>(sender());

    if (clickedButton) {
        qDebug() << "Clicked button text: " << clickedButton->text();

        addCommand(clickedButton);
    }
}

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

