#ifndef _TRANSLATE_OPERATOR_H_
#define _TRANSLATE_OPERATOR_H_

#include <iostream>
#include <vector>

namespace codeGen
{

class TranslateOperator
{
public:
    TranslateOperator() = delete;

    static std::string translateOperator(const std::string& op);
    static std::string negateOperator(const std::string& op);
    static std::string negateAllOperatorsInExpression(const std::string& expression);

    inline static std::vector<std::string> operatorsSymbols = {
           // add sub  mul  sdiv srem shl  ashr slt  sle  sgt  sge  eq   ult  ule  ugt  uge
            "+", "-", "*",  "/",  "%",  "<<", ">>", "<", "<=", ">", ">=", "==", "<", "<=", ">", ">="
    };
};

}   // namespace codeGen

#endif // _TRANSLATE_OPERATOR_H_