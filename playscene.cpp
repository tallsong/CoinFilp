#include "playscene.h"
#include "mypushbutton.h"
#include "mycoin.h"
#include <QDebug>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QPainter>
#include <QTimer>
#include <QLabel>
#include <QPixmap>
//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{
//
//}


PlayScene::PlayScene(int playLevel)
    :m_playLevel{playLevel}
{
    //设置窗口固定大小
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QPixmap(":/img/Coin0001.png"));
    //设置标题
    this->setWindowTitle("play scene");

    //创建菜单栏
    QMenuBar * bar = this->menuBar();
    this->setMenuBar(bar);
    //创建开始菜单
    QMenu * startMenu = bar->addMenu("start");
    //创建按钮菜单项
    QAction * quitAction = startMenu->addAction("quit");
    //点击退出 退出游戏
    connect(quitAction,&QAction::triggered,[=](){this->close();});


    MyPushButton * backButton {new MyPushButton(":/img/BackButton.png",":/img/BackButtonSelected")};
    backButton->setParent(this);
    backButton->move(this->width()-backButton->width(),this->height()-backButton->height());
    connect(backButton,&QPushButton::clicked,[=](){
        QTimer::singleShot(500,this,[=](){
            emit this->chooseSecneBack();
        });
    });

    //创建具体用户选择的关卡标签
      QLabel * label = new QLabel;
      label->setParent(this);

      QString str  = QString("leavel: %1").arg(this->m_playLevel);
      label->setText(str);

      //设置字体和字号
      QFont font;
      font.setFamily("华文新魏");
      font.setPointSize(20);
      label->setFont(font);

      //设置位置和大小
      label->setGeometry(QRect(30,this->height() - 50, 120,50 ));

      for(int i{0};i<4;++i)
      {
          for(int j{0};j<4;++j)
          {
              QLabel* playLabel = new QLabel;
              QPixmap pix;
              pix.load(":/img/BoardNode.png");
              playLabel->setGeometry(0,0,pix.width(),pix.height());
              playLabel->setPixmap(pix);
              playLabel->setParent(this);
              playLabel->move(57+i*pix.width(),200+j*pix.height());
              MyCoin * coin =new MyCoin(":/img/Coin0001.png");
              coin->setParent(this);
              coin->move(59+i*pix.width(),204+j*pix.height());

          }
      }

}


void PlayScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/img/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/img/Title.png");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);
}
