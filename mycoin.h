#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyCoin(QWidget *parent = 0);
    MyCoin(QString imagePath);
    int m_posX;
    int m_posY;
    bool m_flag;
    int m_min{1};
    int m_max{8};
    bool m_isAnimation{false};
    QTimer *m_timer1;
    QTimer *m_timer2;
    void changeFlag();
    void mousePressEvent(QMouseEvent *);
    bool m_isWin{false};
signals:

public slots:
};

#endif // MYCOIN_H
