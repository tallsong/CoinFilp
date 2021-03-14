#include "mainscene.h"
#include "ui_mainscene.h"
#include "mypushbutton.h"
#include"chooselevelscene.h"
#include<QTimer>
#include<QPixmap>
#include<QPaintEvent>
#include<QPainter>
#include<QDebug>
MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);
    this->setWindowTitle("CoinFilp");
    this->setFixedSize(320,588);
    this->setWindowIcon(QIcon{":/img/Coin0001.png"});
    //this->setWindowIcon(QPixmap{":/img/Coin0001.png"});
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });

    ChooseLevelScene *chooseLevelScene  {new ChooseLevelScene};
    MyPushButton * startButton {new MyPushButton(":/img/MenuSceneStartButton.png")};
    startButton->move(this->width()*0.5-startButton->width()*0.5,this->height()*0.7);
    startButton->setParent(this);
    connect(startButton,&QPushButton::clicked,[=](){
        startButton->moveUp();
        startButton->moveDown();
        QTimer::singleShot(500,this,[=](){
            this->hide();
            chooseLevelScene->show();
        });
    });
}

void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap map;
    map.load(":/img/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),map);
    map.load(":/img/Title.png");
    map = map.scaled(map.width()*0.5,map.height()*0.5);
    painter.drawPixmap(10,30,map.width(),map.height(),map);


}
MainScene::~MainScene()
{
    delete ui;
}

