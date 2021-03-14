#include "mypushbutton.h"
#include<QDebug>
//MyPushButton::MyPushButton(QWidget *parent) : QWidget(parent)
//{
//
//}



MyPushButton::MyPushButton(QString normalImagePath,QString pressImagePath)
    :m_normalImagePath{normalImagePath},m_pressImagePath{pressImagePath}
{
    QPixmap pix;
    bool ret{pix.load(this->getNormalImagePath())};
    if(!ret)
    {
        qDebug()<<QString{"wrong path : %1"}.arg(this->getNormalImagePath());
        return;

    }
    else
    {
        qDebug()<<QString{"right path : %1"}.arg(this->getNormalImagePath());
        this->setFixedSize(QSize{pix.width(),pix.height()});
        qDebug()<<"with:"<<pix.width();
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(QIcon{pix});
        this->setIconSize(QSize{pix.width(),pix.height()});


    }

}
