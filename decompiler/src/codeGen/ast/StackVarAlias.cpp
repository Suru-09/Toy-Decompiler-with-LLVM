#include "codeGen/ast/StackVarAlias.h"
#include "logger/LoggerManager.h"

codeGen::ast::StackVarAlias::StackVarAlias(const std::string &basicBlockName, const std::string &localVar, const std::string &stackVarName)
: m_basicBlockName(basicBlockName),
m_localVar(localVar),
m_stackVarName(stackVarName)
{
   logger = logger::LoggerManager::getInstance()->getLogger("codeGen");
}

const std::string &codeGen::ast::StackVarAlias::getBasicBlockName() const
{
   return m_basicBlockName;
}

const std::string &codeGen::ast::StackVarAlias::getLocalVar() const
{
   return m_localVar;
}

const std::string &codeGen::ast::StackVarAlias::getStackVarName() const
{
   return m_stackVarName;
}

void codeGen::ast::StackVarAlias::setBasicBlockName(const std::string &basicBlockName)
{
   m_basicBlockName = basicBlockName;
}

void codeGen::ast::StackVarAlias::setLocalVar(const std::string &localVar)
{
   m_localVar = localVar;
}

void codeGen::ast::StackVarAlias::setStackVarName(const std::string &stackVarName)
{
   m_stackVarName = stackVarName;
}