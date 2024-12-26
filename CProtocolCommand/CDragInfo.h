#ifndef CDRAGINFO_H
#define CDRAGINFO_H

#include <QPoint>
class CCommandReprView;
class CCommandRepr;


class CDragInfo
{
public:
    CDragInfo();

    ~CDragInfo() {}

    void setBlockRepr(CCommandRepr* blockRepr) {_blockRepr = blockRepr;}

    CCommandRepr* getBlockRepr() const {return _blockRepr;}

    void setDropSuccessful(bool successful = true) {_dropSuccessful = successful;}

    bool getDropSuccessful() const {return _dropSuccessful;}

    void setKeepOriginal(bool keep) {_keepOriginal = keep;}

    bool getKeepOriginal() const {return _keepOriginal;}

    void setTopLeft(QPoint topLeft) {_topLeft = topLeft;}

    QPoint getTopLeft() const {return _topLeft;}


private:
    CCommandRepr* _blockRepr{nullptr};

    bool _dropSuccessful{false};

    bool _keepOriginal{true};

    QPoint _topLeft;
};


#endif // CDRAGINFO_H
