#include "chooselevelscene.h"
#include "mypushbutton.h"
#include "playscene.h"
#include <QPainter>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QDebug>
#include <QLabel>
#include <QTimer>
#include <QSound>
ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    QSound *backSound = new QSound(":/img/BackButtonSound.wav", this);
    QSound *chooseSound = new QSound(":/img/TapButtonSound.wav", this);
    QMenuBar *menBar{menuBar()};
    QMenu *startMenu = menBar->addMenu("start");
    QAction *quitAction = startMenu->addAction("quit");
    this->setWindowTitle("choose level scene");
    this->setFixedSize(320, 588);
    this->setWindowIcon(QIcon{":/img/Coin0001.png"});
    connect(quitAction, &QAction::triggered, [=]() {
        this->close();
    });
    MyPushButton *backButton{new MyPushButton(":/img/BackButton.png", ":/img/BackButtonSelected")};
    backButton->setParent(this);
    backButton->move(this->width() - backButton->width(), this->height() - backButton->height());
    connect(backButton, &QPushButton::clicked, [=]() {
        QTimer::singleShot(500, this, [=]() {
            backSound->play();
            emit this->chooseSceneBack();
        });
    });

    //25，130，70
    for (int i{0}; i < 20; i++)
    {
        MyPushButton *menuButton{new MyPushButton(":/img/LevelIcon.png")};
        menuButton->setParent(this);
        menuButton->move(25 + (i % 4) * 70, 130 + (i / 4) * 70);
        connect(menuButton, &QPushButton::clicked, [=]() {
            chooseSound->play();
            //qDebug()<<"you select level "<<i+1;
            this->m_playScene = new PlayScene{i + 1};
            this->hide();
            this->m_playScene->show();

            connect(this->m_playScene, &PlayScene::chooseSecneBack, [=]() {
                delete this->m_playScene;
                this->m_playScene = nullptr;
                this->show();
            });
        });
        QLabel *label{new QLabel(this)};
        label->setFixedSize(menuButton->width(), menuButton->height());
        label->move(25 + (i % 4) * 70, 130 + (i / 4) * 70);
        label->setText(QString::number(i + 1));
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}

void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/img/OtherSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
    pix.load(":/img/Title.png");
    //map = map.scaled(map.width()*0.5,map.height()*0.5);
    painter.drawPixmap((this->width() - pix.width()) * 0.5, 30, pix.width(), pix.height(), pix);
}
