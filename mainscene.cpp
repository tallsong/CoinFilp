#include "mainscene.h"
#include "ui_mainscene.h"

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);
    this->setWindowTitle("CoinFilp");
    this->setFixedSize(300,528);
    this->setWindowIcon(QIcon{":/img/Coin0001.png"});
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });
}

MainScene::~MainScene()
{
    delete ui;
}

