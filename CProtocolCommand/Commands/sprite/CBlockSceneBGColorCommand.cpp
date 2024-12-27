#include "CBlockSceneBGColorCommand.h"
#include "CMessage.h"
#include "CCommandExecuteThread.h"
#include "CValue.h"


CBlockSceneBGColorCommand::CBlockSceneBGColorCommand() {}

CBlockSceneBGColorCommand::~CBlockSceneBGColorCommand()
{
    if(m_SceneColor != nullptr)
    {
        delete m_SceneColor;
        m_SceneColor = nullptr;
    }
}

QList<CCommand::ParamType> CBlockSceneBGColorCommand::getParamTypes() const
{
    QList<CCommand::ParamType> params;
    params.append(CCommand::STRING_EXPRESSION);
    return params;
}

void CBlockSceneBGColorCommand::executeNextStep(CCommandExecuteThread &executionThread) const
{
    if(m_SceneColor == nullptr)
    {
        executionThread.endExecution(nullptr);
        return;
    }

    IntMessage* m = (IntMessage*)executionThread.getMessage();
    if(m == NULL)
    {
        m = new IntMessage(0);
        executionThread.setMessage(m);
    }

    if(m->getValue() == 0)
    {
        executionThread.setNextBlock(m_SceneColor);
        m->setValue(1);
        return;
    }

    if(m->getValue() == 1)
    {
        CValue* value = (CValue*) executionThread.getReturnValue();
        //if no return value -> end execution
        if(value == NULL)
        {
            executionThread.endExecution(NULL);
            return;
        }

        // move sprite
        CSprite* sprite = executionThread.getSprite();
        if(sprite != NULL)
        {
            QString strColor = (QString)value->toString();
            QStringList parts = strColor.split(',');
            if (parts.size() == 3)
            {
                int red   = parts[0].toInt();
                int green = parts[1].toInt();
                int blue  = parts[2].toInt();
                sprite->setBlockSceneBackgroundColor(QColor(red,green,blue));
            }
            executionThread.endExecution(NULL);
            return;
        }
    }
}

bool CBlockSceneBGColorCommand::addParameter(CCommand *parameter, int index)
{
    if(index != 0 || parameter == NULL)
        return false;

    if(parameter->getReturnType() != CCommand::STRING_EXPRESSION && parameter->getReturnType() != CCommand::STRING_EXPRESSION)
        return false;

    m_SceneColor = (CExpressionCommand*)parameter;

    return true;
}
