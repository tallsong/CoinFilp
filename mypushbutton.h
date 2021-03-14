#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyPushButton(QWidget *parent = nullptr);
    MyPushButton(QString normalImagePath,QString pressImagePath="");
    QString getNormalImagePath()
    {
        return this->m_normalImagePath;
    }
    QString getPressImagePath()
    {
        return this->m_pressImagePath;
    }
private:
    QString m_normalImagePath;
    QString m_pressImagePath;
signals:

};

#endif // MYPUSHBUTTON_H
