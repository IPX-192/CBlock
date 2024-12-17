#ifndef CMESSAGE_H
#define CMESSAGE_H

#include "CValue.h"

class CMessage
{
public:
    CMessage();

    virtual ~CMessage() {}
};

class IntMessage : public CMessage
{
public:
    /**
     * @brief Constructor
     */
    IntMessage(int value = 0) : m_iValue(value) {}

    /**
     * @brief Sets the value
     * @param value The value to set
     */
    void setValue(int value) {m_iValue = value;}

    /**4
     * @brief Returns the current value
     * @return The current value
     */
    int getValue() const {return m_iValue;}

private:
    int m_iValue;
};

class ValueMessage : public CMessage
{
public:
    /**
     * @brief Constructor
     * @param value The initial value
     * @param number The initial number
     */
    ValueMessage(CValue* value = NULL, int number = 0) : m_Value(value), m_iMumber(number) {}

    /**
     * @brief Destructor
     */
    virtual ~ValueMessage();

    /**
     * @brief Returns the current value
     * @return The Value pointer
     */
    virtual CValue* getValue() const {return m_Value;}

    /**
     * @brief Sets the value
     * @param value Pointer to the value to set
     */
    virtual void setValue(CValue* value);

    /**
     * @brief Returns the current number
     * @return The number
     */
    virtual int getNumber() const {return m_iMumber;}

    /**
     * @brief Sets the number
     * @param number The number to set
     */
    virtual void setNumber(int number) {m_iMumber = number;}

private:
    CValue* m_Value;
    int m_iMumber;

};

#endif // CMESSAGE_H
