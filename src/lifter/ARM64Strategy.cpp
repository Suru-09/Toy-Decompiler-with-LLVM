#include "lifter/ARM64Strategy.h"

void lifter::ARM64Strategy::visit(std::shared_ptr<IVisitor> v) {
    v->visit(shared_from_this());
}

void lifter::ARM64Strategy::liftELF(const std::string& file) {
    std::cout << "Starting to lift an ARM64 ELF!\n";
}