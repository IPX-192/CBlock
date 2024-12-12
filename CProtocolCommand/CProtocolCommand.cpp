#include "CProtocolCommand.h"
#include "ui_CProtocolCommand.h"
#include <QPushButton>
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


    // QGraphicsRectItem* rectItem = new QGraphicsRectItem(0, 0, 100, 100);
    // scene-> addItem(rectItem);



    // 初始化按钮信息数组
    buttonInfos[0] = {"if", 32, 0};
    buttonInfos[1] = {"else", 32, 50};
    buttonInfos[2] = {"while", 100, 0};
    buttonInfos[3] = {"for", 100, 50};

    buttonInfos[4] = {"+", 32, 100};
    buttonInfos[5] = {"-", 32, 150};
    buttonInfos[6] = {"=", 100, 100};

    buttonInfos[7] = {">", 32, 200};
    buttonInfos[8] = {"<", 100, 150};
    buttonInfos[9] = {"Add", 100, 200};



    for (const auto& info : buttonInfos) {
        CCommandBtn* pushButton = new CCommandBtn(info.text);
        pushButton->setFixedSize(65, 45);
        pushButton->setStyleSheet("color: black;");
        QGraphicsProxyWidget* proxy = scene -> addWidget(pushButton);

        qDebug() << "Setting position: " << info.x << info.y;
        proxy->setPos(info.x, info.y);


        // 使用lambda表达式来连接按钮点击信号和自定义的槽函数逻辑，打印按钮文字
        connect(pushButton, &QPushButton::clicked, this, &CProtocolCommand::onCommandBtnClicked);

        // connect(pushButton, &QPushButton::clicked, [pushButton]() {
        //     qDebug() << "Clicked button text: " << pushButton->text();
        //     CProtocolCommand::addCommand(pushButton->text());

        //     m_test.push_back(pushButton->text());

        // });
    }
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
    qDebug()<<"safasfsafase";

    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
    if (clickedButton) {
        qDebug() << "Clicked button text: " << clickedButton->text();
        // 在这里可以继续进行其他操作，比如调用 addCommand 函数等，根据你的实际需求
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

