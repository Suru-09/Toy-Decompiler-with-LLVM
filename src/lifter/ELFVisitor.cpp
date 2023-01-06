#include "lifter/ELFVisitor.h"


lifter::ELFVisitor::ELFVisitor(const std::string& file_path)
: file(file_path) 
{}

void lifter::ELFVisitor::visit(std::shared_ptr<IArchitectureStrategy> strategy) {
    strategy->liftELF(file);
}