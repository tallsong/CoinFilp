#include "mypushbutton.h"
#include <QDebug>
#include <QPropertyAnimation>
//MyPushButton::MyPushButton(QWidget *parent) : QWidget(parent)
//{
//
//}

MyPushButton::MyPushButton(QString normalImagePath, QString pressImagePath)
    : m_normalImagePath{normalImagePath}, m_pressImagePath{pressImagePath}
{
    QPixmap pix;
    bool ret{pix.load(this->getNormalImagePath())};
    if (!ret)
    {
        qDebug() << QString{"wrong path : %1"}.arg(this->getNormalImagePath());
        return;
    }
    else
    {
        this->setFixedSize(QSize{pix.width(), pix.height()});
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(QIcon{pix});
        this->setIconSize(QSize{pix.width(), pix.height()});
    }
}
void MyPushButton::moveUp()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
    animation->setEndValue(QRect(this->x(), this->y() + 10, this->width(), this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void MyPushButton::moveDown()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(), this->y() + 10, this->width(), this->height()));
    animation->setEndValue(QRect(this->x(), this->y(), this->width(), this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    if (getPressImagePath() != "") //选中路径不为空，显示选中图片
    {
        QPixmap pixmap;
        bool ret = pixmap.load(getPressImagePath());
        if (!ret)
        {
            qDebug() << getPressImagePath() << "加载图片失败!";
        }

        this->setFixedSize(pixmap.width(), pixmap.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(), pixmap.height()));
    }
    //交给父类执行按下事件
    return QPushButton::mousePressEvent(e);
}
void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if (getNormalImagePath() != "") //选中路径不为空，显示选中图片
    {
        QPixmap pixmap;
        bool ret = pixmap.load(getNormalImagePath());
        if (!ret)
        {
            qDebug() << getNormalImagePath() << "加载图片失败!";
        }
        this->setFixedSize(pixmap.width(), pixmap.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(), pixmap.height()));
    }
    return QPushButton::mouseReleaseEvent(e);
}
