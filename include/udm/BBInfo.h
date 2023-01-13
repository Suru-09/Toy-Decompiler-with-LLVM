#ifndef __BB_INFO_H__
#define __BB_INFO_H__

#include <iostream>

namespace udm {

class BBInfo {
public:
    explicit BBInfo();
    bool getIsHeader() const;
    bool getIsLoop() const;
    bool getIsIfStatement() const;
private:
    bool isHeader;
    bool isLoop;
    bool isIfStatement;
};

}   // namespace udm


#endif