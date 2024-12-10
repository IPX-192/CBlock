#ifndef CCOMMANDBTN_H
#define CCOMMANDBTN_H

#include <QPushButton>

class CCommandBtn : public QPushButton
{
public:
    CCommandBtn();

public:
    explicit CCommandBtn(int index, QString text, QObject *parent = 0);

signals:
};

#endif // CCOMMANDBTN_H
