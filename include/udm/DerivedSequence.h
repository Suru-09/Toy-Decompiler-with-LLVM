#ifndef __DERIVED_SEQUENCE_H__
#define __DERIVED_SEQUENCE_H__

#include <iostream>
#include <vector>

#include "udm/IntervalGraph.h"
#include "udm/Interval.h"

#include <llvm/IR/BasicBlock.h>

namespace udm {

class DerivedSequence {
public:
    DerivedSequence() = default;
    DerivedSequence(const udm::IntervalGraph& intervalGraph);

    std::vector<udm::IntervalGraph>& getDerivedSequence() noexcept;
    void setDerivedSequence(const std::vector<udm::IntervalGraph>& derivedSequence) noexcept;
private:
    std::vector<udm::IntervalGraph> derivedSequence;
};

}  // namespace udm

#endif