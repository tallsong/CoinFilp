# evnet
## reimplement focus evnet


```cpp
//socsearchlineedit.h
#ifndef SOCSEARCHLINEEDIT_H
#define SOCSEARCHLINEEDIT_H
#include <QLineEdit>

class SocSearchLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    SocSearchLineEdit(QWidget *parent = 0);

signals:
    void focussed(bool hasFocus);

protected:
    virtual void focusInEvent(QFocusEvent *e);
    virtual void focusOutEvent(QFocusEvent *e);
};

#endif // SOCSEARCHLINEEDIT_H

```

```cpp
//socsearchlineedit.cpp
#include "socsearchlineedit.h"

SocSearchLineEdit::SocSearchLineEdit(QWidget *parent)
    : QLineEdit(parent)
{
}



void SocSearchLineEdit::focusInEvent(QFocusEvent *e)
{
    QLineEdit::focusInEvent(e);
    emit(focussed(true));
}

void SocSearchLineEdit::focusOutEvent(QFocusEvent *e)
{
    QLineEdit::focusOutEvent(e);
    emit(focussed(false));
}

```
```cpp
// main.cpp
//SocSearchLineEdit *staticvsocidSelected;
connect(staticvsocidSelected, &SocSearchLineEdit::focussed, [=](bool isON)
        {
            if (isON) //表示获得了光标
            {
                qDebug() << staticvsocidComboBox->currentIndex();
                if (staticlogtypeComboBox->currentIndex() > 0)
                {
                    staticlogtypeComboBox->setCurrentIndex(0);
                }
            }
        });

```
