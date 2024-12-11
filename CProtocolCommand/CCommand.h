#ifndef CCOMMAND_H
#define CCOMMAND_H

#include <QString>
#include <QObject>
#include <QList>

class CCommandExecuteThread;
class CStatementCommand;

class CCommand
{
public:
    CCommand();

    enum ParamType {NUMBER_EXPRESSION, STRING_EXPRESSION, BOOLEAN_EXPRESSION,
                     NUMBER_VAR, STRING_VAR, BOOLEAN_VAR,
                     NUMBER_LIST, STRING_LIST, BOOLEAN_LIST,
                     SPRITE,
                     EVENT,
                     VOID,
                     FUNCTION_START
    };

    ~CCommand();

    virtual QString getId() const = 0;

    virtual ParamType getReturnType() const = 0;

    virtual QList<ParamType> getParamTypes() const = 0;

    virtual int getNumBodies() const = 0;

    virtual QString getParamDescription() const = 0;

    virtual QString getBodiesDescription() const = 0;

    virtual void executeNextStep(CCommandExecuteThread& executionThread) const = 0;

    virtual bool addParameter(CCommand* parameter, int index) = 0;

    virtual bool addBody(CStatementCommand* body, int index) = 0;

    virtual CCommand* newInstance() const = 0;

    static bool isValidParam(ParamType given, ParamType target);

    static bool isExpressionParam(ParamType paramType);

    static bool isVariableParam(ParamType paramType);

    static bool isListParam(ParamType paramType);

};

#endif // CCOMMAND_H
