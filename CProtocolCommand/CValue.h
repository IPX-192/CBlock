#ifndef CVALUE_H
#define CVALUE_H

#include <QString>
#include <QList>

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

class BooleanValue : public CValue
{
public:
    /**
     * @brief Constructor method
     */
    BooleanValue(bool value) : m_bValue(value) {}

    /**
     * @brief Returns the datatype of the value
     * @return The datatype of the value
     */
    DataType getDataType() const { return BOOLEAN; }

    /**
     * @brief Returns a numeric value of the value
     * @return A numeric value of the value
     */
    double toDouble() const { return m_bValue ? 1.0 : 0.0; }

    /**
     * @brief Returns a string value of the value
     * @return A string value of the value
     */
    QString toString() const { return m_bValue ? QString("true") : QString("false"); }

    /**
     * @brief Returns a boolean value of the value
     * @return A boolean value of the value
     */
    bool toBool() const { return m_bValue; }

    /**
     * @brief Return a copy of the value
     * @return A copy of the value
     */
    CValue* copy() const;

private:
    bool m_bValue;
};

class CValueList
{
public:
    /**
     * @brief Constructor method
     * @param name The name of the list
     * @param type The type of the list
     */
    CValueList() {}

    /**
     * @brief Copy constructor
     * @param list The list to copy
     */
    CValueList(const CValueList& list) {}

    /**
     * @brief Destructor method
     */
    virtual ~CValueList() {}

    /**
     * @brief Returns the name of the list
     * @return The name of the list
     */
    virtual QString getName() const = 0;

    /**
     * @brief Returns the value at a specific index on the list
     * @param pos The position for which to return the value
     * @return The value at position pos
     */
    virtual CValue* getValueAt(int pos) const = 0;

    /**
     * @brief Sets the value at a specific index on the list
     * @param pos The position for which to set the value
     * @param value The value to set
     */
    virtual void setValueAt(int pos, CValue* value) = 0;

    /**
     * @brief Adds a value to the list
     * @param value The value to add
     */
    virtual void addValue(CValue* value) = 0;

    /**
     * @brief Returns the datatype
     * @return The datatype of the list
     */
    virtual CValue::DataType getDataType() const = 0;

    /**
     * @brief Returns the size of a CValueList
     * @return The size of the value list
     */
    virtual int getSize() const = 0;

    /**
     * @brief Returns an exact copy of this CValueList
     * @return An exact copy of this CValueList
     */
    virtual CValueList* copy() const = 0;
};

class SimpleValueList : public CValueList
{
public:
    SimpleValueList(QString name, CValue::DataType type);
    SimpleValueList(const SimpleValueList &list);

    virtual ~SimpleValueList();

    /**
     * @brief Returns the name of the list
     * @return The name of the list
     */
    QString getName() const { return m_qstrName; }

    /**
     * @brief Returns the value at a specific index on the list
     * @param pos The position for which to return the value
     * @return The value at position pos
     */
    CValue* getValueAt(int pos) const;

    /**
     * @brief Sets the value at a specific index on the list
     * @param pos The position for which to set the value
     * @param value The value to set
     */
    void setValueAt(int pos, CValue* value);

    /**
     * @brief Adds a value to the list
     * @param value The value to add
     */
    void addValue(CValue* value);

    /**
     * @brief Returns the datatype
     * @return The datatype of the list
     */
    CValue::DataType getDataType() const { return m_DataType; }

    /**
     * @brief Returns the size of a valuelist
     * @return The size of the value list
     */
    int getSize() const { return m_listValues.size(); }

    /**
     * @brief Returns an exact copy of this ValueList
     * @return An exact copy of this ValueList
     */
    CValueList *copy() const {return new SimpleValueList(*this);}

private:
    /**
     * @brief The name of the list
     */
    QString m_qstrName;

    /**
     * @brief The values in the list
     */
    QList<CValue*> m_listValues;

    /**
     * @brief The datatype of the list
     */
    CValue::DataType m_DataType;
};


#endif // CVALUE_H
