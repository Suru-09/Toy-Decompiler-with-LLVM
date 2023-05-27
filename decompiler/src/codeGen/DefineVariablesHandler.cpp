#include "codeGen/DefineVariablesHandler.h"

#include "logger/LoggerManager.h"
#include "codeGen/Variable.h"
#include "utils/CodeGenUtils.h"
#include "codeGen/ast/PHINodeHandler.h"


#include <llvm/IR/CFG.h>
#include <llvm/ADT/PostOrderIterator.h>
#include <llvm/IR/Instructions.h>

codeGen::DefineVariablesHandler::DefineVariablesHandler(llvm::Function &llvmFn)
: llvmFn(llvmFn)
{
    logger = logger::LoggerManager::getInstance()->getLogger("codeGen");
}

std::map<std::string, std::vector<codeGen::Variable>> codeGen::DefineVariablesHandler::handle() {
    std::map<std::string, std::vector<codeGen::Variable>> variables;

    llvm::ReversePostOrderTraversal<const llvm::Function*> rpot(&llvmFn);
    for(auto bb: rpot)
    {
        auto terminator = bb->getTerminator();
        std::string branchCondition;
        if(auto* branchInstr = llvm::dyn_cast<llvm::BranchInst>(terminator))
        {
            if(branchInstr->isConditional())
            {
                branchCondition = branchInstr->getCondition()->getName().str();
            }
        }

        for(auto& instr: *bb)
        {
            // !!!! --- phi nodes symbolize variables that are saved on the stack,
            // which will later be replaced by the local variables for simplicity.
            // same goes for cast instructions, they are not needed in the decompiled code,
            // creating lots of clutter.
            if(instr.getOpcode() == llvm::Instruction::PHI || instr.getName().empty() || instr.isCast())
            {
                continue;
            }

            // check if variable has no uses && is it only used by as lhs for the function call
            // this was added once I made the decision not to print function calls
            if(instr.getNumUses() == 0 && instr.getOpcode() == llvm::Instruction::Call)
            {
                continue;
            }

            // check if variable has single use && is it only used in branch condition
            // this was added once I made the decision not to print if and while loops
            // conditions as separate variables, instead I print them directly in the
            // if and while loops headers.
            if(utils::CodeGenUtils::doesInstructionHaveSingleUse(&instr) && branchCondition == instr.getName().str())
            {
                continue;
            }

            // check if variable has single use && it is used in a select instruction
            // makes reading easier if the condition does not have a separate variable
            if(utils::CodeGenUtils::isInstructionUsedInTernaryOperatorAndHasSingleUse(&instr))
            {
                continue;
            }

            // get variable type
            logger->info("[DefineVariablesHandler::handle] Variable name added for definition: {}, for type: {}", instr.getName().str(), instr.getOpcodeName());
            auto type = utils::CodeGenUtils::typeToString(instr.getType());
            auto initialValue = getVariableInitialValue(instr);
            Variable var = Variable(instr.getName().str(), type, initialValue);
            if(variables.find(bb->getName().str()) != variables.end())
            {
                // if a variable already exists in the block, then push at the end of the vector.
                variables[bb->getName().str()].push_back(var);
                continue;
            }
            // if a variable does not exist in the block, then create a new vector and insert it into the map.
            variables.insert_or_assign(bb->getName().str(), std::vector<Variable>{var});
        }
    }
    return variables;
}

std::string codeGen::DefineVariablesHandler::getVariableInitialValue(const llvm::Instruction &instr) {
    //  Add support for instruction that are mentioned in a PHI node.
    auto instrName = instr.getName().str();
    auto phiNodeHandler = codeGen::ast::PHINodeHandler(llvmFn);
    for(auto& bb: llvmFn)
    {
        for(auto& localInstr: bb)
        {
            if(localInstr.getOpcode() == llvm::Instruction::PHI)
            {
                auto phiNode = llvm::dyn_cast<llvm::PHINode>(&localInstr);
                if(phiNode)
                {
                    auto labelsAndValues = phiNodeHandler.getLabelsAndValueFromPhiNode(phiNode);
                    auto findInstr = std::find_if(labelsAndValues.begin(), labelsAndValues.end(), [&instrName](auto& labelAndValue){
                        return labelAndValue.second == instrName;
                    });

                    if(findInstr != labelsAndValues.end())
                    {
                        return labelsAndValues.front().second;
                    }
                }
            }
        }
    }

    auto type = utils::CodeGenUtils::typeToString(instr.getType());
    if(type.find('i') != std::string::npos)
    {
        return "0";
    }

    if(type.find('f') != std::string::npos)
    {
        return "0.0";
    }

    if(type.find("bool") != std::string::npos)
    {
        return "false";
    }

    return "0";
}
