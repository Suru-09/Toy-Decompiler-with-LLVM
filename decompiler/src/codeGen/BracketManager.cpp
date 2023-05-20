#include "codeGen/BracketManager.h"
#include "logger/LoggerManager.h"

#include "utils/CodeGenUtils.h"

// intialize static variables
std::map<std::pair<std::string, std::string>, unsigned int> codeGen::BracketManager::bracketMap{};
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

bool codeGen::BracketManager::shouldCloseConditional(const std::string &bbName, const udm::FuncInfo &funcInfo) {
    if (!funcInfo.exists(bbName)) {
        logger->error("[BracketManager::shouldCloseConditional] {} does not exist in funcInfo", bbName);
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

    if(isLoop || !isConditional || isReturn)
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

bool codeGen::BracketManager::shouldCloseLoop(const std::string &bbName, const udm::FuncInfo &funcInfo) {
    // same as conditional but tweak the if statement
    if (!funcInfo.exists(bbName)) {
        logger->error("[BracketManager::shouldCloseLoop] {} does not exist in funcInfo", bbName);
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

    if(!isLoop || isConditional || isReturn)
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

void codeGen::BracketManager::addBracket(const std::string &bbName, const udm::FuncInfo &funcInfo) {
    if (!funcInfo.exists(bbName)) {
        logger->error("[BracketManager::addBracket] {} does not exist in funcInfo", bbName);
        return;
    }

    auto bbInfo = funcInfo.getBBInfo(bbName);
    auto isLoop = bbInfo.getIsLoop() && bbInfo.getLoopType() != udm::BBInfo::LoopType::NONE;
    auto isConditional = !bbInfo.getFollowNode().empty() && bbInfo.getLoopType() == udm::BBInfo::LoopType::NONE;
    std::string latchOrFollowNode;
    if (isLoop) {
        latchOrFollowNode = bbInfo.getHeadToLatch().second;
    }
    else if (isConditional) {
        latchOrFollowNode = bbInfo.getFollowNode();
    }

    if (isLoop || isConditional) {
        auto bracketsIt = std::find_if(bracketMap.begin(), bracketMap.end(), [&bbName](const auto &keyPair) {
            return keyPair.first.second == bbName;
        });

        logger->debug("[BracketManager::addBracket] Adding bracket for {}", bbName);
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
