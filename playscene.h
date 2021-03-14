#ifndef PLAYSCENE_H
#define PLAYSCENE_H

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

private:
    int m_playLevel;
signals:
    void chooseSecneBack();
public slots:
};

#endif // PLAYSCENE_H