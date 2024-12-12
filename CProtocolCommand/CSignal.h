#ifndef CSIGNAL_H
#define CSIGNAL_H
#include <QString>

class CSignal
{
public:
    enum SignalType {START, BUTTONCLICKED, MOUSECLICKED, MESSAGE,
                      ARROW_UP, ARROW_DOWN, ARROW_LEFT, ARROW_RIGHT,
                      SPACE, ENTER};

    CSignal();

    CSignal(SignalType signalType) : m_SignalType(signalType), m_qstrMessage(QString("")) {}

    CSignal(SignalType signalType, const QString& message) : m_SignalType(signalType), m_qstrMessage(message) {}

    QString getMessage() const {return m_qstrMessage;}

    SignalType getType() const {return m_SignalType;}




private:
    SignalType m_SignalType;
    QString m_qstrMessage;
};

#endif // CSIGNAL_H
