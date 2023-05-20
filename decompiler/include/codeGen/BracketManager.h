#ifndef REVERSE_ENGINEERING_TOOL_BRACKETMANAGER_H
#define REVERSE_ENGINEERING_TOOL_BRACKETMANAGER_H

#include <string>
#include <map>
#include <memory>
#include <spdlog/spdlog.h>

#include "udm/BBInfo.h"
#include "udm/FuncInfo.h"

namespace codeGen {

class BracketManager {
public:
    BracketManager() = default;
    ~BracketManager() = default;

    static udm::BBInfo::LoopType isLoop(const udm::BBInfo& bbInfo);
    static bool isConditional(const udm::BBInfo& bbInfo);

    static void addBracket(const std::string& bbName, const udm::FuncInfo& funcInfo);

    static bool shouldCloseConditional(const std::string& bbName, const udm::FuncInfo& funcInfo);
    static bool shouldCloseLoop(const std::string& bbName, const udm::FuncInfo& funcInfo);
    static bool shouldCloseReturn(const std::string& bbName, const udm::FuncInfo& funcInfo);

    /*
     * @param returnBBName: the name of the basic block that we are adding a return value to (practically the place where
     * we close parenthesis).
     * @param funcInfo: We are using it to find the old place for the parenthesis and remove it from the map.
     * @brief When adding a return value, we should close all the brackets that were opened before the return.
     * for example:
     *          if( a  != 1 ) {                      if( a == 1) {
     *              ....                    --->        return value;
     *              ....                            } // !!!! --  This was added now
     *              while(true) {...}               while(true) {...}
 *             }
     */
    static void handleBracketsWhenAddingReturn(const std::string &returnBBName, const udm::FuncInfo &funcInfo,
                                               llvm::Function &llvmFun);

private:
    /*
     *  @brief map containing the name of the basic block and the number of brackets that should be added
     *  before the basic block.
     *  @structure: key -> pair<basic block, latchOrFollowNode> value -> number of brackets to be closed when
     *  reaching the basic block.
     */
    static std::map<std::pair<std::string, std::string> , unsigned int> bracketMap;
    static std::shared_ptr<spdlog::logger> logger;
};

};


#endif //REVERSE_ENGINEERING_TOOL_BRACKETMANAGER_H
