#include "lifter/X86Strategy.h"

void lifter::X86Strategy::visit(std::shared_ptr<IVisitor> v) {
    std::shared_ptr<X86Strategy> x86{shared_from_this()};
    v->visit(x86);
}

void lifter::X86Strategy::lift(const std::string& file) {
}