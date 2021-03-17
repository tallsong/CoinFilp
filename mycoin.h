#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyCoin(QWidget *parent = 0);
    MyCoin(QString imagePath);
    void changeFlag();
    int m_posX;
    int m_posY;
    bool m_flag;
    int m_min{1};
    int m_max{8};
    QTimer *m_timer1;
    QTimer *m_timer2;

signals:

public slots:
};

#endif // MYCOIN_H
