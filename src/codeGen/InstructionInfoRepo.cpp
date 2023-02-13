#include "codeGen/InstructionInfoRepo.h"

#include "logger/LoggerManager.h"
#include "codeGen/InstructionInfo.h"

codeGen::InstructionInfoRepo::InstructionInfoRepo() {
    logger = logger::LoggerManager::getInstance()->getLogger("codeGen");
}

void codeGen::InstructionInfoRepo::insert(InstructionInfo& info) {
    repo.push_back(info);
}

void codeGen::InstructionInfoRepo::remove(InstructionInfo& info) {
    auto find = std::find_if(repo.begin(), repo.end(), [&info](InstructionInfo& i) {
        return i.getName() == info.getName();
    });

    if(find != repo.end())
    {
        repo.erase(find);
    }
}

void codeGen::InstructionInfoRepo::update(InstructionInfo& info) {
    auto find = std::find_if(repo.begin(), repo.end(), [&info](InstructionInfo& i) {
        return i.getName() == info.getName();
    });

    if(find != repo.end())
    {
        *find = info;
    }
}

codeGen::InstructionInfo codeGen::InstructionInfoRepo::getInstructionInfo(const std::string& instrInfoName) {
    auto find = std::find_if(repo.begin(), repo.end(), [&instrInfoName](InstructionInfo& i) {
        return i.getName() == instrInfoName;
    });

    if(find != repo.end())
    {
        return *find;
    }

    logger->warn("[getInstructionInfo] InstructionInfo not found, returning empty InstructionInfo");
    return InstructionInfo();
}

std::string codeGen::InstructionInfoRepo::toString() const
{
    std::string str = "\n";
    for(auto& instrInfo: repo)
    {
        str += instrInfo.toString() + "\n";
    }
    return str;
}