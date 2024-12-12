#ifndef CCOMMANDBTN_H
#define CCOMMANDBTN_H

#include <QPushButton>

#include <QStringList>
#include <QString>
#include <QPoint>
#include <QSize>
#include <QFont>
#include <QList>
#include <QDebug>
#include "CCommand.h"

class CCommandBtn : public QPushButton
{
public:
    CCommandBtn(CCommand* block);
    virtual ~CCommandBtn();

    virtual CCommandBtn* copy();

    QString getId() const { return m_qstrID; }

signals:

private:
    QString m_qstrID;
};

#endif // CCOMMANDBTN_H
