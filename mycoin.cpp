#include "mycoin.h"
#include <QDebug>
#include <QTimer>
//MyCoin::MyCoin(QWidget *parent) : QWidget(parent)
//{

//}

MyCoin::MyCoin(QString imagePath)
{
    QPixmap pix;
    if (!pix.load(imagePath))
    {
        qDebug() << "wrong path:" << imagePath;
        return;
    }
    else
    {
        this->setFixedSize(pix.width(), pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize{pix.width(), pix.height()});

        m_timer1 = new QTimer(this);
        m_timer2 = new QTimer(this);

        connect(m_timer1, &QTimer::timeout, [=]() {
            QPixmap pix;
            QString imagePath = QString(":/img/Coin000%1.png").arg(this->m_min++);
            if (!pix.load(imagePath))
            {
                qDebug() << "wrong path:" << imagePath;
                return;
            }
            else
            {
                this->setFixedSize(pix.width(), pix.height());
                this->setStyleSheet("QPushButton{border:0px;}");
                this->setIcon(pix);
                this->setIconSize(QSize{pix.width(), pix.height()});
            };
            if (this->m_min > this->m_max)
            {
                this->m_min = 1;
                m_timer1->stop();
                this->m_isAnimation = false;
            }
        });
        connect(m_timer2, &QTimer::timeout, [=]() {
            QPixmap pix;
            QString imagePath = QString(":/img/Coin000%1.png").arg(this->m_max--);
            if (!pix.load(imagePath))
            {
                qDebug() << "wrong path:" << imagePath;
                return;
            }
            else
            {
                this->setFixedSize(pix.width(), pix.height());
                this->setStyleSheet("QPushButton{border:0px;}");
                this->setIcon(pix);
                this->setIconSize(QSize{pix.width(), pix.height()});
            };
            if (this->m_min > this->m_max)
            {
                this->m_max = 8;
                m_timer2->stop();
                this->m_isAnimation = false;
            }
        });
    }
}

void MyCoin::changeFlag()
{
    if (this->m_flag)
    {
        this->m_isAnimation = true;
        this->m_timer1->start(30);

        this->m_flag = false;
    }
    else
    {
        this->m_isAnimation = true;
        this->m_timer2->start(30);
        this->m_flag = true;
    }
}
void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if (this->m_isAnimation || this->m_isWin)
    {
        return;
    }
    else
    {
        QPushButton::mousePressEvent(e);
    }
}
