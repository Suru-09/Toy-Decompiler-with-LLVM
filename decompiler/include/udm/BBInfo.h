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

    enum class ConditionalType
    {
        ELSE,
        ELSE_IF,
        IF,
        NONE
    };

    explicit BBInfo();

    bool getIsHeader() const;
    bool getIsLoop() const;
    bool getIsIfStatement() const;
    LoopType getLoopType() const;
    ConditionalType getConditionalType() const;
    std::string getFollowNode() const;
    std::pair<std::string, std::string> getHeadToLatch() const;

    void setIsHeader(bool isHeader);
    void setIsLoop(bool isLoop);
    void setIsIfStatement(bool isIfStatement);
    void setLoopType(LoopType loopType);
    void setFollowNode(std::string followNode);
    void setHeadToLatch(std::pair<std::string, std::string> headToLatch);
    void setConditionalType(ConditionalType type);


    static std::string getLoopTypeString(size_t loopT);
    static std::string getConditionalTypeString(size_t condT);

    void print() const;
    std::string toString() const;
private:
    LoopType loopType;
    ConditionalType conditionalType;
    std::string followNode;
    // first: the header node, second: the latch node
    std::pair<std::string, std::string> headToLatch;
    bool isHeader;
    bool isLoop;
    bool isIfStatement;
    std::shared_ptr<spdlog::logger> logger;

};

}   // namespace udm


#endif