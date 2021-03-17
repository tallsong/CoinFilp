#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H
#include <playscene.h>
#include <QMainWindow>

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    PlayScene *m_playScene;

signals:
    void chooseSceneBack();
};

#endif // CHOOSELEVELSCENE_H
