#ifndef CVALUE_H
#define CVALUE_H

#include <QString>

class CValue
{
public:

    enum DataType {NUMBER, STRING, BOOLEAN};

    CValue();

    virtual ~CValue() {}

    virtual DataType getDataType() const = 0;


    virtual double toDouble() const = 0;

    virtual QString toString() const = 0;

    virtual bool toBool() const = 0;

    virtual CValue* copy() const = 0;

};

class StringValue : public CValue
{
public:
    /**
     * @brief Constructor method
     */
    StringValue(QString value) : m_qstrValue(value) {}

    /**
     * @brief Returns the datatype of the value
     * @return The datatype of the value
     */
    DataType getDataType() const { return STRING; }

    /**
     * @brief Returns a numeric value of the value
     * @return A numeric value of the value
     */
    double toDouble() const { return m_qstrValue.toDouble(); }

    /**
     * @brief Returns a string value of the value
     * @return A string value of the value
     */
    QString toString() const { return m_qstrValue; }

    /**
     * @brief Returns a boolean value of the value
     * @return A boolean value of the value
     */
    bool toBool() const { return m_qstrValue.compare("true", Qt::CaseInsensitive); }

    /**
     * @brief Return a copy of the value
     * @return A copy of the value
     */
    CValue* copy() const;

private:

    QString m_qstrValue;
};


class NumberValue : public CValue
{
public:
    /**
     * @brief Constructor method
     */
    NumberValue(double value) : m_dValue(value) {}

    virtual ~NumberValue() {}

    /**
     * @brief Returns the datatype of the value
     * @return The datatype of the value
     */
    DataType getDataType() const { return NUMBER; }

    /**
     * @brief Returns a numeric value of the value
     * @return A numeric value of the value
     */
    double toDouble() const { return m_dValue; }

    /**
     * @brief Returns a string value of the value
     * @return A string value of the value
     */
    QString toString() const { return QString::number(m_dValue); }

    /**
     * @brief Returns a boolean value of the value
     * @return A boolean value of the value
     */
    bool toBool() const { return (m_dValue > 0.99999 && m_dValue < 1.00001); }

    /**
     * @brief Return a copy of the value
     * @return A copy of the value
     */
    CValue* copy() const;

private:
    double m_dValue;
};

#endif // CVALUE_H
