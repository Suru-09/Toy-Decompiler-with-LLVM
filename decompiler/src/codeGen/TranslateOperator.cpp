#include "codeGen/TranslateOperator.h"


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
