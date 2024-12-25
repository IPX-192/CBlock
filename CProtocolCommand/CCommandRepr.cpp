#include "CCommandRepr.h"
#include "CCommandParam.h"
#include <QPushButton>
#include <QStyleOptionButton>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

using std::max;

QFont CCommandRepr::FONT = QFont("Arial", 11, QFont::DemiBold);

const int CCommandRepr::MARGIN = 3;

const int CCommandRepr::MARGIN_HORIZONTAL = 5;

const int CCommandRepr::LEFT_GUTTER = 10;

const int CCommandRepr::FOOTER_HEIGHT = 10;

const int CCommandRepr::FOOTER_WIDTH = 50;

const QSize CCommandRepr::HOLDER_SIZE = QSize(48, 14);

class CCommandParam;
CCommandRepr::CCommandRepr(CCommand *block)
{
    CCommandRepr::FONT.setPixelSize(11);

    m_qstrID = block->getId();
    m_ReturnType = block->getReturnType();
    m_strListParamLabels = block->getParamDescription().split("%p");
    for (int i = 0; i < m_strListParamLabels.size(); ++i) {
        m_strListParamLabels.replace(i, m_strListParamLabels.at(i).trimmed());
    }
    m_strListBodyLabels = block->getBodiesDescription().split("%b", QString::SkipEmptyParts);
    for (int i = 0; i < m_strListBodyLabels.size(); ++i) {
        m_strListBodyLabels.replace(i, m_strListBodyLabels.at(i).trimmed());
    }

    foreach (CCommand::ParamType type, block->getParamTypes()) {
        _params.append(new CCommandParam(type));
    }

    for (int i = 0; i < block->getNumBodies(); ++i) {
        _bodies.append(NULL);
    }

    calculateSizes(true, true, true);
    calculatePositions(true, true, true);
}

CCommandRepr::CCommandRepr(const CCommandRepr& repr)
{
    CCommandRepr::FONT.setPixelSize(11);

    m_qstrID = repr.getId();
    m_ReturnType = repr.getReturnType();
    m_strListParamLabels = repr.getParamDescriptions();
    m_strListBodyLabels = repr.getBodyDescriptions();

    for (int i = 0; i < repr.getNumParams(); i++) {
        CCommandParam* p = new CCommandParam(repr.getParamType(i));
        if(repr.getParam(i) != NULL) {
            CCommandRepr* newParam = repr.getParam(i)->copy();
            newParam->setParent(this);
            p->setBlock(newParam);
        }
        _params.append(p);
    }

    for (int i = 0; i < repr.getNumBodies(); ++i) {
        CCommandRepr* body = repr.getBody(i);

        if (body == NULL)
            _bodies.append(NULL);
        else {
            CCommandRepr* newBody = body->copy();
            newBody->setParent(this);
            _bodies.append(newBody);
        }
    }
    if (repr._nextBlock != NULL) {
        _nextBlock = repr._nextBlock->copy();
        _nextBlock->setParent(this);
    } else
        _nextBlock = NULL;
    _isLocked = repr._isLocked;
    _position = repr._position;
    calculateSizes(true, true, true);
    calculatePositions(true, true, true);
}

CCommandRepr::CCommandRepr(CCommand::ParamType type, QString name, bool isVar)
{
    CCommandRepr::FONT.setPixelSize(11);

    if(isVar) {
        m_qstrID = QString("Var"); //used for creating variables
        m_strListParamLabels.append(name);
    } else {
        QString cat;
        if (type == CCommand::NUMBER_EXPRESSION)
            cat = "Number";
        else if (type == CCommand::BOOLEAN_EXPRESSION)
            cat = "Boolean";
        else
            cat = "String";
        m_qstrID = cat + QString("_") + name; //used for creating true and false

        if (name == "true")
            m_strListParamLabels.append(tr("true"));
        else
            m_strListParamLabels.append(tr("false"));
    }
    m_ReturnType = type;
    calculateSizes(true, true, true);
    calculatePositions(true, true, true);
}

CCommandRepr::CCommandRepr(CCommand::ParamType type)
{
    CCommandRepr::FONT.setPixelSize(11);
    if(type == CCommand::STRING_EXPRESSION)
    {
        m_qstrID = "String_String";
    }

    else if (type == CCommand::NUMBER_EXPRESSION)
    {
        m_qstrID = "Number_Number";
    }

    else if (type == CCommand::SPRITE)
    {
        m_qstrID = "Sprite_Sprite";
    }

    else if (type == CCommand::FUNCTION_START)
    {
        m_qstrID = "Function_Start";
    }

    m_ReturnType = type;

    calculateSizes(true, true, true);
    calculatePositions(true, true, true);
}

CCommandRepr::~CCommandRepr()
{
    if (_nextBlock != NULL)
        delete _nextBlock;

    foreach (CCommandRepr* b, _bodies) {
        if (b != NULL)
            delete b;
    }

    foreach (CCommandParam* p, _params) {
        if (p != NULL)
            delete p;
    }
}

QSize CCommandRepr::getSize()
{
    return _size;
}

QSize CCommandRepr::getTotalSize()
{
    return _totalSize;
}

QSize CCommandRepr::getHeaderSize()
{
    return _headerSize;
}

QSize CCommandRepr::getBodyDescriptionSize(int index)
{
    if (index < 0 || index >= m_strListBodyLabels.size())
        return QSize();

    return getFontRect(m_strListBodyLabels.at(index)).size() + QSize(MARGIN * 3, MARGIN * 2);
}

QSize CCommandRepr::getBodySize(int index)
{
    if (_bodies.at(index) == NULL)
        return HOLDER_SIZE;

    return _bodies.at(index)->getTotalSize();
}

QSize CCommandRepr::getParamDescriptionsize(int index)
{
    if (index < 0 || index >= m_strListParamLabels.size())
        return QSize();

    return getFontRect(m_strListParamLabels.at(index)).size();
}

QSize CCommandRepr::getParamSize(int index)
{
    // voorlopig niet nodig
    return QSize();
}

QPoint CCommandRepr::getParamPosition(int index)
{
    return _paramPositions.at(index);
}

QPoint CCommandRepr::getParamDescriptionPosition(int index)
{
    return _paramLabelPositions.at(index);
}

QPoint CCommandRepr::getBodyDescriptionPosition(int index)
{
    if (index < 0 || index >= m_strListBodyLabels.size())
        return QPoint();

    QPoint pos(LEFT_GUTTER + MARGIN, getParamListSize().height() + MARGIN);

    for (int i = 0; i < _bodies.size(); ++i) {
        if (index == i)
            return pos + QPoint(0, getFontRect(m_strListBodyLabels.at(index)).height()/2);

        pos += QPoint(0, getBodySize(i).height() + 19);
    }

    return QPoint();
}

QPoint CCommandRepr::getBodyPosition(int index)
{
    QPoint pos(LEFT_GUTTER, getHeaderSize().height());

    for (int i = 0; i < index; ++i) {
        pos += QPoint(0, getBodySize(i).height());
        pos += QPoint(0, getBodyDescriptionSize(i+1).height());
    }

    return pos;
}

QPoint CCommandRepr::getNextStatementPosition()
{
    return QPoint(0, getSize().height());
}

bool CCommandRepr::doesBodyFit(CCommandRepr* repr, int index)
{
    if(repr == NULL)
        return false;

    return (repr->getReturnType() == CCommand::VOID);
}

bool CCommandRepr::placeBody(CCommandRepr* repr, int index)
{
    if(repr == NULL)
        return false;

    if (!doesBodyFit(repr, index))
        return false;

    _bodies.replace(index, repr);
    repr->setParent(this);

    emitBlockUpdated(false, true, false);

    return true;
}

bool CCommandRepr::doesParamFit(CCommandRepr* repr, int index)
{
    if(repr == NULL)
        return false;

    CCommand::ParamType expected = _params.at(index)->getParamType();
    CCommand::ParamType type = repr->getReturnType();

    if (expected == type)
        return true;
    if (expected == CCommand::NUMBER_EXPRESSION && type == CCommand::NUMBER_VAR)
        return true;
    if (expected == CCommand::BOOLEAN_EXPRESSION && type == CCommand::BOOLEAN_VAR)
        return true;
    if (expected == CCommand::STRING_EXPRESSION && type == CCommand::STRING_VAR)
        return true;

    return false;
}

bool CCommandRepr::placeParam(CCommandRepr* repr, int index)
{
    if(repr == NULL)
        return false;

    if (!doesParamFit(repr, index))
        return false;

    _params.at(index)->setBlock(repr);
    repr->setParent(this);

    emitBlockUpdated(true, false, false);

    return true;
}

//重要，设置下一个物块的方法在这里
bool CCommandRepr::placeNextStatement(CCommandRepr* repr)
{
    if(repr == NULL)
        return false;

    if (!doesBodyFit(repr, -1))
        return false;

    //这里是读取xml文件中设置下一个物块的方法
    _nextBlock = repr;
    repr->setParent(this);

    emitBlockUpdated(false, false, true);

    return true;
}

bool CCommandRepr::removeBody(int index)
{
    _lastRemovedWasParam = false;
    _lastRemovedIndex = index;
    _lastRemoved = _bodies.at(index);

    _bodies.replace(index, NULL);

    emitBlockUpdated(false, true, false);

    return true;
}

bool CCommandRepr::removeParam(int index)
{
    _lastRemovedWasParam = true;
    _lastRemovedIndex = index;
    _lastRemoved = _params.at(index)->getBlock();

    _params.at(index)->setBlock(NULL);

    emitBlockUpdated(true, false, false);

    return true;
}

bool CCommandRepr::removeNextStatement()
{
    _lastRemovedWasParam = false;
    _lastRemovedIndex = -1;
    _lastRemoved = _nextBlock;

    _nextBlock = NULL;

    emitBlockUpdated(false, false, true);

    return true;
}

bool CCommandRepr::removeFromParent()
{
    return true;
}

bool CCommandRepr::remove(CCommandRepr* repr)
{
    int index = 0;
    bool found = false;
    foreach (CCommandRepr* b, _bodies) {
        if (b == repr) {
            found = true;
            break;
        }
        index++;
    }

    if (found)
        return removeBody(index);

    index = 0;
    found = false;
    foreach (CCommandParam* p, _params) {
        if (p->getBlock() == repr) {
            found = true;
            break;
        }
        index++;
    }

    if (found)
        return removeParam(index);

    if (repr == _nextBlock)
        return removeNextStatement();

    return false;
}

int CCommandRepr::getNumBodies() const
{

    return _bodies.size();
}

int CCommandRepr::getNumParams() const
{
    return _params.size();
}

CCommandRepr* CCommandRepr::getBody(int index) const
{
    if (index < 0 || index >= _bodies.size())
        return NULL;

    return _bodies.at(index);
}

CCommandRepr* CCommandRepr::getParam(int index) const
{
    if (index < 0 || index >= _params.size())
        return NULL;

    return _params.at(index)->getBlock();
}

CCommand::ParamType CCommandRepr::getParamType(int index) const
{
    return _params.at(index)->getParamType();
}

QRect CCommandRepr::getFontRect(QString string)
{
    QFontMetrics metrics(FONT);
    return metrics.boundingRect(string);
}

QSize CCommandRepr::getParamListSize()
{
    return _paramListSize;
}

void CCommandRepr::revert()
{
    return;
}

void CCommandRepr::revertToParent()
{
    if (_lastRemoved == NULL)
        return;

    if (_lastRemovedWasParam)
        placeParam(_lastRemoved, _lastRemovedIndex);
    else if (_lastRemovedIndex >= 0)
        placeBody(_lastRemoved, _lastRemovedIndex);
    else
        placeNextStatement(_lastRemoved);
}

void CCommandRepr::emitBlockUpdated(bool param, bool body, bool next) {
    calculateSizes(param, body, next);
    calculatePositions(param, body, next);

    emit blockUpdated();

    if(_parent != NULL)
        _parent->emitBlockUpdated(true, true, true);
}

void CCommandRepr::calculateSizes(bool param, bool body, bool next)
{
    if (param) {
        calculateParamListSize();
        calculateHeaderSize();
    }
    if (param || body) {
        calculateSize();
    }
    if (param || body || next) {
        calculateTotalSize();
    }
}

void CCommandRepr::calculatePositions(bool param, bool body, bool next)
{
    calculateParamPositions();
    calculateParamLabelPositions();
}

void CCommandRepr::calculateTotalSize()
{
    QSize total = getSize();

    // next block
    if (_nextBlock != NULL) {
        QSize s = _nextBlock->getTotalSize();
        total += QSize(0, s.height());
        total.setWidth(max(total.width(), s.width()));
    } else if (m_ReturnType == CCommand::VOID || m_ReturnType == CCommand::EVENT) {
        QSize s = HOLDER_SIZE;
        total += QSize(0, s.height());
        total.setWidth(max(total.width(), s.width()));
    }

    _totalSize = total;
}

void CCommandRepr::calculateSize()
{
    QSize total(0, 0);

    // header size
    QSize header = getHeaderSize();
    total += header;

    // size of body descriptions (starts at 1 because description 0 is in header)
    for (int i = 1; i < m_strListBodyLabels.size(); ++i) {
        QSize s = getBodyDescriptionSize(i);
        total += QSize(0, s.height());
        total.setWidth(max(total.width(), s.width()));
    }

    // bodies
    foreach(CCommandRepr* body, _bodies) {
        QSize s;
        if (body == NULL)
            s = HOLDER_SIZE;
        else
            s = body->getTotalSize();
        total += QSize(0, s.height());
        total.setWidth(max(total.width(), s.width()));
    }

    // fixed footer
    if (m_strListBodyLabels.size() > 0) {
        total += QSize(0, FOOTER_HEIGHT);
    }

    if (m_ReturnType == CCommand::VOID || m_ReturnType == CCommand::EVENT)
        total += QSize(LEFT_GUTTER, 0);
    else
        total += QSize(2, 0);

    _size = total;
}

void CCommandRepr::calculateParamListSize()
{
    QSize params(MARGIN, 2 * MARGIN);
    for (int i = 0; i < max(_params.size(), m_strListParamLabels.size()); ++i) {
        if (i < m_strListParamLabels.size()) {
            params += QSize(getFontRect(m_strListParamLabels.at(i)).size().width() + MARGIN_HORIZONTAL, 0);
            params.setHeight(max(params.height(), 2 * MARGIN + getFontRect(m_strListParamLabels.at(i)).size().height()));
        }

        if (i < _params.size()) {
            CCommandRepr* block = _params.at(i)->getBlock();
            if (block != NULL) {
                params += QSize(block->getTotalSize().width() + MARGIN_HORIZONTAL, 0);
                params.setHeight(max(params.height(), 2 * MARGIN + block->getTotalSize().height()));
            } else {
                params += QSize(HOLDER_SIZE.width() + MARGIN_HORIZONTAL, 0);
                params.setHeight(max(params.height(), 2 * MARGIN + HOLDER_SIZE.height()));
            }
        }
    }

    _paramListSize = params;
}

void CCommandRepr::calculateHeaderSize()
{
    QSize firstBodyDesc = getBodyDescriptionSize(0);
    firstBodyDesc -= QSize(0, MARGIN);

    // calculate params and text
    QSize params = getParamListSize();

    if (m_strListBodyLabels.size() == 0)
        _headerSize = params;
    else
        _headerSize = QSize(max(params.width(), firstBodyDesc.width()), params.height() + firstBodyDesc.height());
}

void CCommandRepr::calculateParamPositions()
{
    _paramPositions.clear();
    int margin = (getReturnType() == CCommand::VOID || getReturnType() == CCommand::EVENT) ? LEFT_GUTTER : 0;
    QSize params(margin + MARGIN, 2 * MARGIN);
    for (int i = 0; i < max(_params.size(), m_strListParamLabels.size()); ++i) {
        if (i < m_strListParamLabels.size()) {
            params += QSize(getFontRect(m_strListParamLabels.at(i)).size().width() + MARGIN_HORIZONTAL, 0);
            params.setHeight(max(params.height(), 2 * MARGIN + getFontRect(m_strListParamLabels.at(i)).size().height()));
        }

        if (i < _params.size()) {
            CCommandRepr* block = _params.at(i)->getBlock();

            QPoint result;
            result.setX(params.width());
            if (block != NULL)
                result.setY(getParamListSize().height()/2 - block->getTotalSize().height()/2);
            else
                result.setY(getParamListSize().height()/2 - HOLDER_SIZE.height()/2);
            _paramPositions.append(result);

            if (block != NULL) {
                params += QSize(block->getTotalSize().width() + MARGIN_HORIZONTAL, 0);
                params.setHeight(max(params.height(), 2 * MARGIN + block->getTotalSize().height()));
            } else {
                params += QSize(HOLDER_SIZE.width() + MARGIN_HORIZONTAL, 0);
                params.setHeight(max(params.height(), 2 * MARGIN + HOLDER_SIZE.height()));
            }
        }
    }
}

void CCommandRepr::calculateParamLabelPositions()
{
    _paramLabelPositions.clear();
    int margin = (getReturnType() == CCommand::VOID || getReturnType() == CCommand::EVENT) ? LEFT_GUTTER : 0;
    QSize params(margin + MARGIN, 2 * MARGIN);
    for (int i = 0; i < max(_params.size(), m_strListParamLabels.size()); ++i) {
        if (i < m_strListParamLabels.size()) {
            _paramLabelPositions.append(QPoint(params.width(), getParamListSize().height()/2 + getFontRect(m_strListParamLabels.at(i)).height()/2 - MARGIN + 1));

            params += QSize(getFontRect(m_strListParamLabels.at(i)).size().width() + MARGIN_HORIZONTAL, 0);
            params.setHeight(max(params.height(), 2 * MARGIN + getFontRect(m_strListParamLabels.at(i)).size().height()));
        }

        if (i < _params.size()) {
            CCommandRepr* block = _params.at(i)->getBlock();

            if (block != NULL) {
                params += QSize(block->getTotalSize().width() + MARGIN_HORIZONTAL, 0);
                params.setHeight(max(params.height(), 2 * MARGIN + block->getTotalSize().height()));
            } else {
                params += QSize(HOLDER_SIZE.width() + MARGIN_HORIZONTAL, 0);
                params.setHeight(max(params.height(), 2 * MARGIN + HOLDER_SIZE.height()));
            }
        }
    }
}

void CCommandRepr::duplicateBlock()
{

}

void CCommandRepr::deleteBlock()
{
    this->removeFromParent();
    delete this;
}

CCommandRepr* CCommandRepr::copy()
{
    return new CCommandRepr(*this);
}

void CCommandRepr::setParamLabels(QStringList paramLabels)
{
    m_strListParamLabels = paramLabels;
    emitBlockUpdated(true, true, true);
}

void CCommandRepr::setParamLabels(QString paramLabels)
{
    m_strListParamLabels = paramLabels.split("%p");;
    emitBlockUpdated(true, true, true);
}

void CCommandRepr::setParamTypes(QList<CCommand::ParamType> paramTypes)
{
    //delete params
    foreach (CCommandParam* p, _params) {
        if (p != NULL)
            delete p;
    }
    _params.clear();

    //create new params
    foreach (CCommand::ParamType type, paramTypes) {
        _params.append(new CCommandParam(type));
    }
    emitBlockUpdated(true, true, true);
}
