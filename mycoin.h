#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyCoin(QWidget *parent = 0);
    MyCoin(QString imagePath);

signals:

public slots:
};

#endif // MYCOIN_H
