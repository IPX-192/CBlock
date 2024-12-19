#ifndef COBJECT_H
#define COBJECT_H

//控制的对象类

#include<QString>
#include "CCommandExcuteHandler.h"

class CObject
{
public:
    CObject();
    ~CObject();


   // void setExecutionHandler(CCommandExcuteHandler* test);

   // CCommandExcuteHandler* getExecutionHandler();

    int m_iValue{0};
    QString m_strValue{""};
    bool m_bValue{false};

private:

    //CCommandExcuteHandler* m_pExcuteHandler{nullptr};
};

#endif // COBJECT_H
