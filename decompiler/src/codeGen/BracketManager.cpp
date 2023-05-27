#include "codeGen/BracketManager.h"
#include "logger/LoggerManager.h"

#include "utils/CodeGenUtils.h"
#include <llvm/IR/Instructions.h>

// intialize static variables
//std::map<std::pair<std::string, std::string>, unsigned int> codeGen::BracketManager::bracketMap{};
std::shared_ptr<spdlog::logger> codeGen::BracketManager::logger = logger::LoggerManager::getInstance()->getLogger("codeGen");


udm::BBInfo::LoopType codeGen::BracketManager::isLoop(const udm::BBInfo &bbInfo) {
    if (bbInfo.getIsLoop() && bbInfo.getIsLoop()) {
        return bbInfo.getLoopType();
    }
    return udm::BBInfo::LoopType::NONE;
}

bool codeGen::BracketManager::isConditional(const udm::BBInfo &bbInfo) {
    if ( bbInfo.getIsLoop() || bbInfo.getLoopType() != udm::BBInfo::LoopType::NONE) {
        return false;
    }
    return !bbInfo.getFollowNode().empty();
}

udm::BBInfo::ConditionalType codeGen::BracketManager::shouldCloseConditional(const std::string &bbName, const udm::FuncInfo &funcInfo) {
    if (!funcInfo.exists(bbName)) {
        logger->error("[BracketManager::shouldCloseConditional] {} does not exist in funcInfo", bbName);
        return udm::BBInfo::ConditionalType::NONE;
    }
    // search for bbName in the BracketMap for the second element of the pair
    auto foundBB = std::find_if(bracketMap.begin(), bracketMap.end(), [&bbName](const auto &keyPair) {
        return keyPair.first.second == bbName;
    });

    if (foundBB == bracketMap.end()) {
        return udm::BBInfo::ConditionalType::NONE;
    }

    auto isLoop = false, isConditional = false, isReturn = false;
    auto conditionalType = udm::BBInfo::ConditionalType::NONE;
    if (funcInfo.exists(foundBB->first.first)) {
        auto bbInfo = funcInfo.getBBInfo(foundBB->first.first);
        isLoop = bbInfo.getIsLoop() && bbInfo.getLoopType() != udm::BBInfo::LoopType::NONE;
        isConditional = !bbInfo.getFollowNode().empty() && bbInfo.getLoopType() == udm::BBInfo::LoopType::NONE;
        conditionalType = bbInfo.getConditionalType()  == udm::BBInfo::ConditionalType::NONE ? udm::BBInfo::ConditionalType::IF : bbInfo.getConditionalType();
    }
    isReturn = foundBB->first.first == "return";

    if(isLoop || !isConditional || isReturn)
    {
        return udm::BBInfo::ConditionalType::NONE;
    }

    if (foundBB->second > 1) {
        bracketMap[foundBB->first]--;
        return conditionalType;
    }
    else {
        bracketMap.erase(foundBB);
        return conditionalType;
    }
}

udm::BBInfo::LoopType codeGen::BracketManager::shouldCloseLoop(const std::string &bbName, const udm::FuncInfo &funcInfo) {
    // same as conditional but tweak the if statement
    if (!funcInfo.exists(bbName)) {
        logger->error("[BracketManager::shouldCloseLoop] {} does not exist in funcInfo", bbName);
        return udm::BBInfo::LoopType::NONE;
    }
    // search for bbName in the BracketMap for the second element of the pair
    auto foundBB = std::find_if(bracketMap.begin(), bracketMap.end(), [&bbName](const auto &keyPair) {
        return keyPair.first.second == bbName;
    });

    if (foundBB == bracketMap.end()) {
        return udm::BBInfo::LoopType::NONE;
    }

    auto loopType = udm::BBInfo::LoopType::NONE;
    auto isLoop = false, isConditional = false, isReturn = false;
    if (funcInfo.exists(foundBB->first.first)) {
        auto bbInfo = funcInfo.getBBInfo(foundBB->first.first);
        isLoop = bbInfo.getIsLoop() && bbInfo.getLoopType() != udm::BBInfo::LoopType::NONE;
        isConditional = !bbInfo.getFollowNode().empty() && bbInfo.getLoopType() == udm::BBInfo::LoopType::NONE;
        loopType = bbInfo.getLoopType();
    }
    isReturn = foundBB->first.first == "return";

    if(!isLoop || isConditional || isReturn)
    {
        return udm::BBInfo::LoopType::NONE;
    }

    if (foundBB->second > 1) {
        bracketMap[foundBB->first]--;
        return loopType;
    }
    else {
        bracketMap.erase(foundBB);
        return loopType;
    }
}

void
codeGen::BracketManager::addBracket(const std::string &bbName, const udm::FuncInfo &funcInfo, llvm::Function &llvmFunc) {
    if (!funcInfo.exists(bbName)) {
        logger->error("[BracketManager::addBracket] {} does not exist in funcInfo", bbName);
        return;
    }

    auto bbInfo = funcInfo.getBBInfo(bbName);
    auto conditionalType = bbInfo.getConditionalType();
    auto isLoop = bbInfo.getIsLoop() && bbInfo.getLoopType() != udm::BBInfo::LoopType::NONE;
    auto isConditional = !bbInfo.getFollowNode().empty() && bbInfo.getLoopType() == udm::BBInfo::LoopType::NONE;
    std::string latchOrFollowNode;
    if (isLoop) {
        latchOrFollowNode = bbInfo.getHeadToLatch().second;
    }
    else if (isConditional) {
        latchOrFollowNode = bbInfo.getFollowNode();
    }

//     handle simple ELSE
//     should add close bracket for the first if
    if(isConditional && conditionalType == udm::BBInfo::ConditionalType::ELSE)
    {
        // get first branch of the conditional
        auto basicBlock = utils::CodeGenUtils::getBBAfterLabel(llvmFunc, bbName);
        if(basicBlock)
        {
            const auto terminator = basicBlock->getTerminator();
            if(terminator)
            {
                if( auto* branchInst = llvm::dyn_cast<llvm::BranchInst>(terminator))
                {
                    if(branchInst->isConditional())
                    {
                        auto* firstIFBB = branchInst->getSuccessor(1);
                        auto firstIFBBName = firstIFBB->getName().str();
                        auto bracketsIt = std::find_if(bracketMap.begin(), bracketMap.end(), [&firstIFBBName](const auto &keyPair) {
                            return keyPair.first.first == firstIFBBName && keyPair.first.second == "ELSE";
                        });

                        if (bracketsIt == bracketMap.end()) {
                            logger->info("[BracketManager::addBracket] Adding bracket for ELSE in block: {}, with first if branch: {}", bbName, firstIFBBName);
                            bracketMap[std::make_pair(firstIFBBName, "ELSE")] = 1;
                        }
                        else
                        {
                            logger->info("[BracketManager::addBracket] Adding bracket for ELSE in block: {}, with first if branch: {}, to the already existing ones", bbName, firstIFBBName);
                            bracketMap[bracketsIt->first]++;
                        }
                    }
                }
            }
        }

    }

    if (isLoop || isConditional) {
        auto bracketsIt = std::find_if(bracketMap.begin(), bracketMap.end(), [&bbName](const auto &keyPair) {
            return keyPair.first.second == bbName;
        });

        logger->info("[BracketManager::addBracket] Adding bracket for {}", bbName);
        if (bracketsIt == bracketMap.end()) {
            bracketMap[std::make_pair(bbName, latchOrFollowNode)] = 1;
        }
        else {
            bracketMap[bracketsIt->first]++;
        }
    }
}

void
codeGen::BracketManager::handleBracketsWhenAddingReturn(const std::string &returnBBName, const udm::FuncInfo &funcInfo,
                                                        llvm::Function &llvmFun) {
    if(!funcInfo.exists(returnBBName))
    {
        logger->error("[BracketManager::handleBracketsWhenAddingReturn] {} does not exist in funcInfo", returnBBName);
        return;
    }

    // delete the closing bracket for the old one
    auto bbInfo = funcInfo.getBBInfo(returnBBName);
    auto isLoop = bbInfo.getIsLoop() && bbInfo.getLoopType() != udm::BBInfo::LoopType::NONE;
    auto isConditional = !bbInfo.getFollowNode().empty() && bbInfo.getLoopType() == udm::BBInfo::LoopType::NONE;
    std::string latchOrFollowNode;
    if (isLoop) {
        latchOrFollowNode = bbInfo.getHeadToLatch().second;
    }
    else if (isConditional) {
        latchOrFollowNode = bbInfo.getFollowNode();
    }

    auto oldBracketsIt = std::find_if(bracketMap.begin(), bracketMap.end(), [&latchOrFollowNode](const auto &keyPair) {
        return keyPair.first.second == latchOrFollowNode;
    });

    if(oldBracketsIt == bracketMap.end())
    {
        logger->error("[BracketManager::handleBracketsWhenAddingReturn] Could not find the old bracket for: ", latchOrFollowNode);
        return;
    }

    if(oldBracketsIt->second > 1)
    {
        logger->info("[BracketManager::handleBracketsWhenAddingReturn] Decreasing the bracket count for: {}", latchOrFollowNode);
        bracketMap[oldBracketsIt->first]--;
    }
    else
    {
        logger->info("[BracketManager::handleBracketsWhenAddingReturn] Erasing the bracket for: {}", latchOrFollowNode);
        bracketMap.erase(oldBracketsIt);
    }

    // add the new one with returnBBName.
    auto newBracketsIt = std::find_if(bracketMap.begin(), bracketMap.end(), [&returnBBName](const auto &keyPair) {
        return keyPair.first.second == returnBBName;
    });

    auto currentBlock = utils::CodeGenUtils::getBBAfterLabel(llvmFun, returnBBName);
    auto nextBB = currentBlock ? currentBlock->getNextNode() : nullptr;
    std::string bbTobeAdded = returnBBName;
    if(nextBB) {
        bbTobeAdded = nextBB->getName().str();
    }
    else {
        logger->error("[BracketManager::handleBracketsWhenAddingReturn] Could not find the next BB after: {}", returnBBName);
    }

    if(newBracketsIt == bracketMap.end())
    {
        logger->info("[BracketManager::handleBracketsWhenAddingReturn] Adding new single bracket for:  {}.", bbTobeAdded);
        bracketMap[std::make_pair("return", bbTobeAdded)] = 1;
    }
    else
    {
        logger->info("[BracketManager::handleBracketsWhenAddingReturn] Adding another bracket for: {}, on the already existing ones.", bbTobeAdded);
        bracketMap[newBracketsIt->first]++;
    }
}

bool codeGen::BracketManager::shouldCloseReturn(const std::string &bbName, const udm::FuncInfo &funcInfo) {
    if (!funcInfo.exists(bbName)) {
        logger->error("[BracketManager::shouldCloseReturn] {} does not exist in funcInfo", bbName);
        return false;
    }

    // search for bbName in the BracketMap for the second element of the pair
    auto foundBB = std::find_if(bracketMap.begin(), bracketMap.end(), [&bbName](const auto &keyPair) {
        return keyPair.first.second == bbName;
    });

    if (foundBB == bracketMap.end()) {
        return false;
    }

    auto isLoop = false, isConditional = false, isReturn = false;
    if (funcInfo.exists(foundBB->first.first)) {
        auto bbInfo = funcInfo.getBBInfo(foundBB->first.first);
        isLoop = bbInfo.getIsLoop() && bbInfo.getLoopType() != udm::BBInfo::LoopType::NONE;
        isConditional = !bbInfo.getFollowNode().empty() && bbInfo.getLoopType() == udm::BBInfo::LoopType::NONE;
    }
    isReturn = foundBB->first.first == "return";

    if(isLoop || isConditional || !isReturn)
    {
        return false;
    }

    if (foundBB->second > 1) {
        bracketMap[foundBB->first]--;
        return true;
    }
    else {
        bracketMap.erase(foundBB);
        return true;
    }
}

bool codeGen::BracketManager::shouldCloseElse(const std::string &bbName, const udm::FuncInfo &funcInfo,
                                              llvm::Function &llvmFunc) {
    if (!funcInfo.exists(bbName)) {
        logger->error("[BracketManager::shouldCloseElse] {} does not exist in funcInfo", bbName);
        return false;
    }

    // search for bbName in the BracketMap for the second element of the pair
    auto foundBB = std::find_if(bracketMap.begin(), bracketMap.end(), [&bbName](const auto &keyPair) {
        return keyPair.first.first == bbName && keyPair.first.second == "ELSE";
    });

    if (foundBB == bracketMap.end()) {
        return false;
    }

    return true;

    if (foundBB->second > 1) {
        logger->info("[BracketManager::shouldCloseElse] Closing else in the block: {}.", bbName);
        //bracketMap[foundBB->first]--;
        return true;
    }
    else {
        //foundBB = bracketMap.erase(foundBB);
        return true;
    }

}
