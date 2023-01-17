#ifndef __BB_INFO_H__
#define __BB_INFO_H__

#include <iostream>
#include <memory>

#include "spdlog/spdlog.h"

namespace udm {

class BBInfo {
public:
    enum class LoopType
    {
        WHILE, DO_WHILE, INFINITE, NONE
    };

    enum class IFTYPE
    {
        NONE
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
    void setFollowNode(std::string followNode);
    std::string getFollowNode() const;

    static std::string getLoopTypeString(size_t loopT);
    void print() const;
private:
    LoopType loopType;
    std::string followNode;
    bool isHeader;
    bool isLoop;
    bool isIfStatement;
    std::shared_ptr<spdlog::logger> logger;

};

}   // namespace udm


#endif