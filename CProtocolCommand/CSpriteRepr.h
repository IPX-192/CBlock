#ifndef CSPRITEREPR_H
#define CSPRITEREPR_H

#include <QList>
#include <QPixmap>
#include "CVarCommandRepr.h"

class CSpriteRepr : public QObject
{
    Q_OBJECT

public:
    CSpriteRepr(QString name = QString());

    CSpriteRepr(const CSpriteRepr &sprite);

    ~CSpriteRepr();

    QString getName() const { return m_qstrName; }

    void setName(QString name);

    void addVariable(CVarCommandRepr* var);

    void removeVariable(CVarCommandRepr* var);

    bool hasVariableWithName(QString name);

    QList<CVarCommandRepr*> getVars() const { return m_listVars; }


signals:
    void nameChanged();

private:
    QString m_qstrName;
    QList<CVarCommandRepr*> m_listVars;

};

#endif // CSPRITEREPR_H
