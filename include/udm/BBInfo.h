#ifndef __BB_INFO_H__
#define __BB_INFO_H__

#include <iostream>

namespace udm {

class BBInfo {
public:
    enum class LoopType
    {
        WHILE, DO_WHILE, INFINITE, NONE
    };

    explicit BBInfo();
    bool getIsHeader() const;
    bool getIsLoop() const;
    bool getIsIfStatement() const;
    LoopType getLoopType() const;
    void setIsHeader(bool isHeader);
    void setIsLoop(bool isLoop);
    void setIsIfStatement(bool isIfStatement);
    void setLoopType(LoopType loopType);

    void print() const;
private:
    LoopType loopType;
    bool isHeader;
    bool isLoop;
    bool isIfStatement;
};

}   // namespace udm


#endif