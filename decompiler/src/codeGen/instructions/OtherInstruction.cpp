#include "codeGen/instructions/OtherInstruction.h"
#include "codeGen/TranslateOperator.h"
#include "utils/CodeGenUtils.h"

#include <llvm/IR/Instructions.h>
#include <llvm/IR/InstrTypes.h>

#include <iostream>

codeGen::OtherInstruction::OtherInstruction(llvm::Instruction& inst, int numSpaces) {
    bool printLhs = utils::CodeGenUtils::canAssignTo(&inst) && inst.getNumUses() > 0;
    if(printLhs)
    {
        instructionString += inst.getName().str() + " = ";
    }
    if(auto* cmpOp = llvm::dyn_cast<llvm::CmpInst>(&inst))
    {
        instructionString += handleCmpInst(cmpOp, numSpaces);
    }

    if(auto* phiNode = llvm::dyn_cast<llvm::PHINode>(&inst))
    {
        instructionString += handlePhiNode(phiNode);
    }

    if(auto* selectInst = llvm::dyn_cast<llvm::SelectInst>(&inst))
    {
        instructionString += handleSelectInst(selectInst);
    }

    if(auto* callInst = llvm::dyn_cast<llvm::CallInst>(&inst))
    {
        // If the function call returns a value, then we need to print the lhs
        // Otherwise, we don't need to print the lhs, because the function call
        // is a void function.
        if(!utils::CodeGenUtils::doesFunctionCallReturn(callInst))
        {
            instructionString = "";
        }
        instructionString += handleCallInst(callInst);
    }

    if(auto* allocaInst = llvm::dyn_cast<llvm::AllocaInst>(&inst))
    {
        instructionString += handleAllocaInst(allocaInst);
    }

    if(auto* storeInst = llvm::dyn_cast<llvm::StoreInst>(&inst))
    {
        instructionString += handleStoreInst(storeInst);
    }

    if(auto* loadInst = llvm::dyn_cast<llvm::LoadInst>(&inst))
    {
        instructionString += handleLoadInst(loadInst);
    }
}

std::string codeGen::OtherInstruction::toString() {
    return instructionString;
}

std::string codeGen::OtherInstruction::handleCmpInst(llvm::CmpInst* cmpInst, int numSpaces) {
    std::string cmpString;
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

    auto llvmValueToString = [](llvm::Value* value){
        std::string str;
        if(llvm::ConstantInt* constInt = llvm::dyn_cast<llvm::ConstantInt>(value))
        {
            str += std::to_string(constInt->getSExtValue());
        }
        else if(llvm::ConstantFP* constFP = llvm::dyn_cast<llvm::ConstantFP>(value))
        {
            str += std::to_string(constFP->getValueAPF().convertToDouble());
        }
        else
        {
            str += value->getName().str();
        }
        return str;
    };

    for(size_t i = 0; i < phiNode->getNumIncomingValues(); ++i)
    {
        llvm::Value* incomingValue = phiNode->getIncomingValue(i);
        std::string incomingBlock = phiNode->getIncomingBlock(i)->getName().str();
        phiString += "[ value:{" + llvmValueToString(incomingValue) + "}, label:{" + incomingBlock + "}], ";
    }
    return phiString;
}

std::string codeGen::OtherInstruction::handleSelectInst(llvm::SelectInst* selectInst) {
    std::string selectString = "";

    std::string condition = utils::CodeGenUtils::llvmValueToString(selectInst->getCondition());
    std::string trueValue = utils::CodeGenUtils::llvmValueToString(selectInst->getTrueValue());
    std::string falseValue = utils::CodeGenUtils::llvmValueToString(selectInst->getFalseValue());
    selectString += condition + " ? " + trueValue + " : " + falseValue;
    return selectString;
}

std::string codeGen::OtherInstruction::handleCallInst(llvm::CallInst* callInst) {
    std::string callString = callInst->getCalledFunction()->getName().str() + "(";
    bool first = true;
    for(auto& operand : callInst->operands())
    {

        std::string name = operand->getName().str();
        if(name.empty()) {  // might be a value, not an instruction.
            name = utils::CodeGenUtils::llvmValueToString(operand);
        }

        // skip the last operand, which is the function name itself.
        if(name == callInst->getCalledFunction()->getName().str())
        {
            continue;
        }

        callString += !first ? ", " : "";
        callString += name;
        first = false;
    }
    callString += ")";
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
    std::string storeInstrStr = "";
    storeInstrStr += storeInst->getPointerOperand()->getName().str() + " = ";
    llvm::Value* value = storeInst->getValueOperand();
    std::string secondOperand = "";
    if(value && !value->hasName())
    {
        if(llvm::ConstantInt* constInt = llvm::dyn_cast<llvm::ConstantInt>(value))
        {
            secondOperand = std::to_string(constInt->getSExtValue());
        }
        else if(llvm::ConstantFP* constFP = llvm::dyn_cast<llvm::ConstantFP>(value))
        {
            secondOperand = std::to_string(constFP->getValueAPF().convertToDouble());
        }
    }
    else
    {
        secondOperand = value->getName().str();
    }
    logger->error("Store instruction: {} -> {}", storeInst->getPointerOperand()->getName().str(), secondOperand);
    storeInstrStr += secondOperand;
    return secondOperand;
}

std::string codeGen::OtherInstruction::handleLoadInst(llvm::LoadInst* loadInst)
{
    return loadInst->getPointerOperand()->getName().str();
}