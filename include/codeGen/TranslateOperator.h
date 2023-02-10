#ifndef _TRANSLATE_OPERATOR_H_
#define _TRANSLATE_OPERATOR_H_

#include <iostream>

namespace codeGen
{

class TranslateOperator
{
public:
    TranslateOperator() = delete;

    static std::string translateOperator(const std::string& op);
};

}   // namespace codeGen

#endif // _TRANSLATE_OPERATOR_H_