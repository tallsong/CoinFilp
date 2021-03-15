#include "mycoin.h"
#include <QDebug>
//MyCoin::MyCoin(QWidget *parent) : QWidget(parent)
//{

//}

MyCoin:: MyCoin(QString imagePath)
{
    QPixmap pix;
    if(!pix.load(imagePath))
    {
        qDebug()<<"wrong path:"<<imagePath;
        return;
    }
    else
    {
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize{pix.width(),pix.height()});

    }
}
