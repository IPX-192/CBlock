#ifndef CCOMMANDREPR_H
#define CCOMMANDREPR_H

#include <QStringList>
#include <QString>
#include <QPoint>
#include <QSize>
#include <QFont>
#include <QList>
#include <QDebug>
#include "CCommand.h"

//组合框
class CCommandRepr : public QObject
{
    Q_OBJECT
public:

    CCommandRepr(CCommand* block);


    CCommandRepr(const CCommandRepr& repr);


    virtual ~CCommandRepr();


    virtual CCommandRepr* copy();


    QString getId() const { return _id; }


    void setPosition(QPoint pos) { _position = pos; }

    QPoint getPosition() const { return _position; }


    void setParent(CCommandRepr* parent) { _parent = parent; _holderParent = NULL; }


    CCommandRepr* getParent() const { return _parent; }


    virtual QSize getTotalSize();


    virtual QSize getSize();


    virtual QSize getHeaderSize();


    QSize getBodyDescriptionSize(int index);


    QSize getBodySize(int index);


    QSize getParamDescriptionsize(int index);


    QSize getParamSize(int index);


    bool doesBodyFit(CCommandRepr* repr, int index);


    bool placeBody(CCommandRepr* repr, int index);


    bool doesParamFit(CCommandRepr* repr, int index);


    bool placeParam(CCommandRepr* repr, int index);


    bool placeNextStatement(CCommandRepr* repr);


    bool removeBody(int index);


    bool removeParam(int index);


    bool removeNextStatement();


    bool removeFromParent();


    bool remove(CCommandRepr* repr);

    int getNumBodies() const;


    int getNumParams() const;

    CCommandRepr* getBody(int index) const;

    CCommandRepr* getParam(int index) const;


    CCommandRepr* getNextStatement() { return _nextBlock; }


    CCommand::ParamType getReturnType() const { return _returnType; }


    CCommand::ParamType getParamType(int index) const;


    QStringList getParamDescriptions() const { return _paramLabels; }


    QStringList getBodyDescriptions() const { return _bodyLabels; }

    QPoint getParamPosition(int index);


    QPoint getBodyPosition(int index);

    QPoint getParamDescriptionPosition(int index);


    QPoint getBodyDescriptionPosition(int index);


    QPoint getNextStatementPosition();


    void revert();

    void setLock(bool locked = true) {_isLocked = locked;}


    bool isLocked() const {return _isLocked;}


    virtual bool isConstantCCommandRepr() const { return false; }


    virtual bool isVarCCommandRepr() const { return false; }


    virtual bool isSpriteCCommandRepr() const { return false; }


    virtual bool isUserStatementRepr() const { return false; }



    static QFont FONT;

    static const int MARGIN;

    static const int MARGIN_HORIZONTAL;

    static const int LEFT_GUTTER;

    static const int FOOTER_HEIGHT;

    static const int FOOTER_WIDTH;

    static const QSize HOLDER_SIZE;

protected:
    CCommandRepr(CCommand::ParamType type, QString name, bool locked = false, bool isVar = true);
    CCommandRepr(CCommand::ParamType type, bool locked = false);

    void setParamLabels(QStringList paramLabels);
    void setParamLabels(QString paramLabels);
    void setParamTypes(QList<CCommand::ParamType> paramTypes);

    void emitBlockUpdated(bool param, bool body, bool next);

signals:
    void blockUpdated();

public slots:
    void duplicateBlock();
    void deleteBlock();

private:
    QString _id;
    CCommandRepr* _parent{nullptr};
    CCommand::ParamType _returnType;
    QStringList _paramLabels;
    QList<CCommandParam*> _params;     //一个单独的块里面的参数
    QStringList _bodyLabels;
    QList<CCommandRepr*> _bodies;   //一个块里面的语句是一个单独的块
    QPoint _position;
    CCommandRepr* _nextBlock{nullptr};
    bool _lastRemovedWasParam{false};
    int _lastRemovedIndex;
    CCommandRepr* _lastRemoved{nullptr};
    bool _isLocked;

    QRect getFontRect(QString string);
    QSize getParamListSize();

    void revertToParent();

    void calculateSizes(bool param, bool body, bool next);
    void calculateTotalSize();
    void calculateSize();
    void calculateParamListSize();
    void calculateHeaderSize();

    void calculatePositions(bool param, bool body, bool next);
    void calculateParamPositions();
    void calculateParamLabelPositions();

    // Sizes
    QSize _totalSize;
    QSize _size;
    QSize _paramListSize;
    QSize _headerSize;
    QList<QPoint> _paramPositions;
    QList<QPoint> _paramLabelPositions;
};

#endif // CCOMMANDREPR_H
