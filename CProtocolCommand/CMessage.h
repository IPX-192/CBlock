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
    IntMessage(int value = 0) : _value(value) {}

    /**
     * @brief Sets the value
     * @param value The value to set
     */
    void setValue(int value) {_value = value;}

    /**
     * @brief Returns the current value
     * @return The current value
     */
    int getValue() const {return _value;}

private:
    int _value;
};

class ValueMessage : public CMessage
{
public:
    /**
     * @brief Constructor
     * @param value The initial value
     * @param number The initial number
     */
    ValueMessage(CValue* value = NULL, int number = 0) : _value(value), _number(number) {}

    /**
     * @brief Destructor
     */
    virtual ~ValueMessage();

    /**
     * @brief Returns the current value
     * @return The Value pointer
     */
    virtual CValue* getValue() const {return _value;}

    /**
     * @brief Sets the value
     * @param value Pointer to the value to set
     */
    virtual void setValue(CValue* value);

    /**
     * @brief Returns the current number
     * @return The number
     */
    virtual int getNumber() const {return _number;}

    /**
     * @brief Sets the number
     * @param number The number to set
     */
    virtual void setNumber(int number) {_number = number;}

private:
    CValue* _value;
    int _number;

};

#endif // CMESSAGE_H
