#include "codeGen/instructions/OtherInstruction.h"
#include "codeGen/TranslateOperator.h"
#include "utils/CodeGenUtils.h"

#include <llvm/IR/Instructions.h>
#include <llvm/IR/InstrTypes.h>

#include <iostream>
#include <vector>


codeGen::OtherInstruction::OtherInstruction(llvm::Instruction& inst, int numSpaces) {
    if(llvm::CmpInst* cmpOp = llvm::dyn_cast<llvm::CmpInst>(&inst))
    {
        instructionString += handleCmpInst(cmpOp, numSpaces);
    }

    if(llvm::PHINode* phiNode = llvm::dyn_cast<llvm::PHINode>(&inst))
    {
        instructionString += handlePhiNode(phiNode);
    }

    if(llvm::SelectInst* selectInst = llvm::dyn_cast<llvm::SelectInst>(&inst))
    {
        instructionString += handleSelectInst(selectInst);
    }

    if(llvm::CallInst* callInst = llvm::dyn_cast<llvm::CallInst>(&inst))
    {
        instructionString += handleCallInst(callInst);
    }

    if(llvm::AllocaInst* allocaInst = llvm::dyn_cast<llvm::AllocaInst>(&inst))
    {
        instructionString += handleAllocaInst(allocaInst);
    }

    if(llvm::StoreInst* storeInst = llvm::dyn_cast<llvm::StoreInst>(&inst))
    {
        instructionString += handleStoreInst(storeInst);
    }

    if(llvm::LoadInst* loadInst = llvm::dyn_cast<llvm::LoadInst>(&inst))
    {
        instructionString += handleLoadInst(loadInst);
    }
}

std::string codeGen::OtherInstruction::toString() {
    return instructionString;
}

std::string codeGen::OtherInstruction::handleCmpInst(llvm::CmpInst* cmpInst, int numSpaces) {
    std::string cmpString = "";
    if(cmpInst->isIntPredicate())
    {
        cmpString += handleIntCmpInst(cmpInst);
    }
    else if(cmpInst->isFPPredicate())
    {
        cmpString += handleFPCmpInst(cmpInst);
    }
    return cmpString;
}

std::string codeGen::OtherInstruction::handleIntCmpInst(llvm::CmpInst* cmpInst) {
    std::string iCmpString = "";
    bool first = true;
    for(auto& operand : cmpInst->operands())
    {
        std::string name = operand->getName().str();
        iCmpString += !first ? " " : "";
        iCmpString += name + " ";

        if(name.empty())
        {
            if(llvm::ConstantInt* constInt = llvm::dyn_cast<llvm::ConstantInt>(operand))
            {
                iCmpString += std::to_string(constInt->getSExtValue());
            }
        }

        if(!first)
        {
            continue;
        }

        first = false;
        std::string predicate = cmpInst->getPredicateName(cmpInst->getPredicate()).str();
        iCmpString += codeGen::TranslateOperator::translateOperator(predicate);
    }
    return iCmpString;
}

std::string codeGen::OtherInstruction::handleFPCmpInst(llvm::CmpInst* cmpInst) {
    std::string fpCmpString = "";
    bool first = true;
    for(auto& operand : cmpInst->operands())
    {
        std::string name = operand->getName().str();
        fpCmpString += !first ? " " : "";
        fpCmpString += name + " ";

        if(name.empty())
        {
            if(llvm::ConstantFP* constFP = llvm::dyn_cast<llvm::ConstantFP>(operand))
            {
                fpCmpString += std::to_string(constFP->getValueAPF().convertToDouble());
            }
        }

        if(!first)
        {
            continue;
        }

        first = false;
        std::string predicate = cmpInst->getPredicateName(cmpInst->getPredicate()).str();
        fpCmpString += codeGen::TranslateOperator::translateOperator(predicate);
    }
    return fpCmpString;
}

std::string codeGen::OtherInstruction::handlePhiNode(llvm::PHINode* phiNode) {
    std::string phiString = "";
    bool first = true;
    for(auto& operand : phiNode->operands())
    {
        std::string name = operand->getName().str();
        phiString += !first ? ", " : "";
        phiString += name + " ";
        first = false;
    }
    return phiString;
}

std::string codeGen::OtherInstruction::handleSelectInst(llvm::SelectInst* selectInst) {
    std::string selectString = "";

    auto handleOperand = [](llvm::Value* operand) {
        std::string name = operand->getName().str();
        std::string result = name + " ";
        if(name.empty())
        {
            if(llvm::ConstantInt* constInt = llvm::dyn_cast<llvm::ConstantInt>(operand))
            {
                result += std::to_string(constInt->getSExtValue());
            }
            else if(llvm::ConstantFP* constFP = llvm::dyn_cast<llvm::ConstantFP>(operand))
            {
                result += std::to_string(constFP->getValueAPF().convertToDouble());
            }
        }
        return result;
    };

    std::string condition = handleOperand(selectInst->getCondition());
    std::string trueValue = handleOperand(selectInst->getTrueValue());
    std::string falseValue = handleOperand(selectInst->getFalseValue());
    selectString += condition + "?" + trueValue + " : " + falseValue;
    return selectString;
}

std::string codeGen::OtherInstruction::handleCallInst(llvm::CallInst* callInst) {
    std::string callString = "";
    bool first = true;
    for(auto& operand : callInst->operands())
    {
        std::string name = operand->getName().str();
        callString += !first ? ", " : "";
        callString += name + " ";
        first = false;
    }
    return callString;
}

std::string codeGen::OtherInstruction::handleAllocaInst(llvm::AllocaInst* allocaInst) {
    std::string allocaString = "";
    auto type = utils::CodeGenUtils::typeToString(allocaInst->getAllocatedType());
    // allocaString += type + " " + allocaInst->getName().str();
    allocaString += allocaInst->getName().str();
    return allocaString;
}

std::string codeGen::OtherInstruction::handleStoreInst(llvm::StoreInst* storeInst)
{
    return storeInst->getValueOperand()->getName().str();
}

std::string codeGen::OtherInstruction::handleLoadInst(llvm::LoadInst* loadInst)
{
    return loadInst->getPointerOperand()->getName().str();
}