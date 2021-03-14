#include "chooselevelscene.h"
#include"mypushbutton.h"
#include<QPainter>
#include<QMenu>
#include<QMenuBar>
#include<QAction>
ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    QMenuBar* menBar{menuBar()};
    QMenu *startMenu = menBar->addMenu("start");
    QAction * quitAction = startMenu->addAction("quit");
    this->setWindowTitle("choose level scene");
    this->setFixedSize(320,588);
    this->setWindowIcon(QIcon{":/img/Coin0001.png"});
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });
    MyPushButton * backButton {new MyPushButton(":/img/BackButton.png",":/img/BackButtonSelected")};
    backButton->setParent(this);
    backButton->move(this->width()-backButton->width(),this->height()-backButton->height());
    connect(backButton,&QPushButton::clicked,[=](){
        emit this->chooseSecneBack();
    });
}



void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/img/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/img/Title.png");
    //map = map.scaled(map.width()*0.5,map.height()*0.5);
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);


}
