#include "codeGen/TranslateOperator.h"

#include <spdlog/spdlog.h>

#include <algorithm>

std::string codeGen::TranslateOperator::translateOperator(const std::string& op)
{
    if(op == "add")
    {
        return "+";
    }
    else if(op == "sub")
    {
        return "-";
    }
    else if(op == "mul")
    {
        return "*";
    }
    else if(op == "sdiv")
    {
        return "/";
    }
    else if(op == "srem")
    {
        return "%";
    }
    else if(op == "shl")
    {
        return "<<";
    }
    else if(op == "ashr")
    {
        return ">>";
    }
    else if(op == "slt")
    {
        return "<";
    }
    else if(op == "sle")
    {
        return "<=";
    }
    else if(op == "sgt")
    {
        return ">";
    }
    else if(op == "sge")
    {
        return ">=";
    }
    else if(op == "eq")
    {
        return "==";
    }
    else if(op == "ult")
    {
        return "<";
    }
    else if(op == "ule")
    {
        return "<=";
    }
    else if(op == "ugt")
    {
        return ">";
    }
    else if(op == "uge")
    {
        return ">=";
    }

    return op;
}

std::string codeGen::TranslateOperator::negateOperator(const std::string &op) {
    // operators are in the same order as in the operatorsSymbols vector
    std::vector<std::string> negatedOperators = {
         // "+", "-", "*",  "/",  "%",  "<<", ">>", "<", "<=", ">", ">=", "==", "<", "<=", ">", ">="
            "-", "+", "*", "/", "%", ">>", "<<", ">=", ">", "<=", "<", "!=", ">=", ">", "<=", "<"
    };

    auto it = std::find(operatorsSymbols.begin(), operatorsSymbols.end(), op);
    if(it != operatorsSymbols.end())
    {
        spdlog::error("Negating operator: {}, returning value: {}", op, negatedOperators[it - operatorsSymbols.begin()]);
        return negatedOperators[it - operatorsSymbols.begin()];
    }


    return op;
}

std::string codeGen::TranslateOperator::negateAllOperatorsInExpression(const std::string &expression) {
    std::string result = expression;
    // replace all operators with their negated version, e.g. < with >=, traverse the string and replace all operators
    // but keep in mind that after replacing one operator we might try to replace the new operator again, so we need to
    // skip the new operator

    std::size_t lastIndex = 0;
    for(const auto& op : operatorsSymbols)
    {
        std::size_t pos = lastIndex;
        while((pos = result.find(op, pos)) != std::string::npos)
        {
            result.replace(pos, op.length(), negateOperator(op));
            pos += negateOperator(op).length();
            lastIndex = pos;
        }
    }


    return result;
}
