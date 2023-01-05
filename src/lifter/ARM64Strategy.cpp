#include "lifter/ARM64Strategy.h"

void lifter::ARM64Strategy::visit(std::shared_ptr<IVisitor> v) {
    std::shared_ptr<ARM64Strategy> arm{shared_from_this()};
    v->visit(arm);
}

void lifter::ARM64Strategy::lift(const std::string& file) {

}