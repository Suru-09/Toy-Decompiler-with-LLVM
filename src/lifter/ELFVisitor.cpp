#include "lifter/ELFVisitor.h"

void lifter::ELFVisitor::visit(std::shared_ptr<ARM64Strategy> arm) {
    // POSSIBLE FUTURE IMPLEMENTATION FOR ARM
    std::cout << "At the moment ARM ELFs are not supported!\n";
}


void lifter::ELFVisitor::visit(std::shared_ptr<X86Strategy> x86) {
    
}