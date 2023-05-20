#include "codeGen/CodeGeneration.h"
#include "codeGen/BranchConditionalGen.h"
#include "codeGen/GenerateFnHeader.h"
#include "codeGen/GenerateFnBody.h"
#include "codeGen/RenameVariables.h"
#include "codeGen/LoopHandler.h"
#include "codeGen/instructions/Instruction.h"
#include "logger/LoggerManager.h"
#include "utils/CodeGenUtils.h"
#include "codeGen/ast/LlvmFunctionNode.h"
#include "codeGen/ast/LlvmBasicBlockNode.h"
#include "codeGen/ast/LlvmInstructionNode.h"
#include "codeGen/ast/GenerateFileVisitor.h"
#include "settings/LifterSettings.h"


#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/ErrorOr.h"
#include "llvm/IR/Function.h"
#include "llvm/ADT/PostOrderIterator.h"
#include <llvm/Analysis/LoopInfo.h>
#include <llvm/IR/Dominators.h>
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Analysis/LoopPass.h"

#include <vector>


codeGen::CodeGeneration::CodeGeneration(const std::string& irFile, std::unordered_map<std::string, udm::FuncInfo> fnInfoMap) 
: irFile(irFile), 
funcInfoMap(fnInfoMap) 
{
    logger = logger::LoggerManager::getInstance()->getLogger("codeGen");
}

void codeGen::CodeGeneration::generate() {
    logger->info("Generating code for IR file: " + irFile);

    llvm::LLVMContext context;
    llvm::SMDiagnostic error;

    std::unique_ptr<llvm::Module> mod = llvm::parseIRFile(irFile, error, context);

    if (!mod) {
        logger->critical("Couldn't open the file with LLVM IR!");
        exit(1);
    }

    for(llvm::Function &f: mod->functions())
    {
        auto fName = f.getName().str();
        auto funcInfo = funcInfoMap[fName];
        processFunction(f, funcInfo);
    }
}

void codeGen::CodeGeneration::fillInstructionNode(llvm::Instruction* instr, std::shared_ptr<ast::LlvmInstructionNode> root)
{
    std::vector<unsigned int> dontAdd = {
      llvm::Instruction::Br
    };

    if (std::find(dontAdd.begin(), dontAdd.end(), instr->getOpcode()) != dontAdd.end())
    {
        return;
    }

    std::shared_ptr<codeGen::Instruction> instruction = codeGen::Instruction::getInstruction(*instr, 0);
    if(instruction)
    {
        root->setInstructionBody(instruction->toString());
        root->setOpcode(instr->getOpcode());
    }
    else
    {
        logger->error("[CodeGeneration::fillInstructionNode] Instruction not found: {}", instr->getOpcodeName());
    }
}

void codeGen::CodeGeneration::processFunction(llvm::Function& f, const udm::FuncInfo& funcInfo)
{
    std::vector<std::string> functionNames = {"calc_sum",
                                              "fibo", "main", "n_way_conditional_switch", "while_pre_tested_loop",
                                              "while_post_tested_loop", "two_way", "for_loop", "if_else", "nested_if_else", "switch_case"
    };

    if(std::find(functionNames.begin(), functionNames.end(), f.getName().str()) == functionNames.end())
    {
        return;
    }

    codeGen::RenameVariables renameVariables(f);
    auto aliasMap = renameVariables.rename();

    logger->info("Processing function: " + f.getName().str());
    std::shared_ptr<ast::LlvmFunctionNode> root = std::make_shared<ast::LlvmFunctionNode>(f.getName().str());

    llvm::ReversePostOrderTraversal<llvm::Function*> rpot(&f);
    for(auto &bb: rpot)
    {
//        spdlog::error("Basic block: {}", bb->getName().str());
        std::shared_ptr<ast::LlvmBasicBlockNode> bbNode = std::make_shared<ast::LlvmBasicBlockNode>(bb->getName().str());
        for(auto & inst : *bb)
        {
            auto instName = inst.getName().str();
            std::shared_ptr<ast::LlvmInstructionNode> instNode = std::make_shared<ast::LlvmInstructionNode>(instName);
            fillInstructionNode(&inst, instNode);
            bbNode->addChild(instNode);
        }
        root->addChild(bbNode);
    }

    std::shared_ptr<ast::GenerateFileVisitor> visitor = std::make_shared<ast::GenerateFileVisitor>(f);
    visitor->setFuncInfo(funcInfo);
    root->accept(visitor);

    std::string decompiledFunction = "\n";
    codeGen::GenerateFnHeader fnHeaderGenerator(f);
    decompiledFunction += fnHeaderGenerator.generate();
    auto output = visitor->getOutput();

    for(auto &bb: rpot)
    {
        auto key = bb->getName().str();
        if (output.find(key) == output.end())
        {
            logger->error("Basic block not found: <{}>", key);
            continue;
        }

        decompiledFunction += "Basic Block: <" + key + ">\n";
        for(const auto& el: output[key])
        {
            decompiledFunction += + "\t" + el + "\n";
        }
    }
    decompiledFunction += "}\n";


    logger->error("Decompiled function: {}", decompiledFunction);
    auto extractLastFileFromPath = [](const std::string& path) -> std::string {
        auto pos = path.find_last_of("/\\");
        return pos != std::string::npos ? path.substr(pos + 1) : path;
    };
    const std::string& path = settings::LifterSettings::getInstance()->getBinaryPath();
    logger->info("[CodeGeneration::processFunction] Writing output to file: {}", extractLastFileFromPath(path) + "_" + f.getName().str());
    visitor->writeToFile(extractLastFileFromPath(path) + "_" + f.getName().str());
}