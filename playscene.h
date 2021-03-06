#ifndef PLAYSCENE_H
#define PLAYSCENE_H
#include "mycoin.h"
#include <QMainWindow>

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = 0);
    PlayScene(int playLevel);
    void paintEvent(QPaintEvent *);
    int getPlayLevel()
    {
        return m_playLevel;
    }
    int m_array[4][4];
    MyCoin *m_coinList[4][4];
    bool m_isWin{true};

private:
    int m_playLevel;
signals:
    void chooseSecneBack();
public slots:
};

#endif // PLAYSCENE_H
