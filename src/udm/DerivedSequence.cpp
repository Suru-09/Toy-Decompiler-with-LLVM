#include "udm/DerivedSequence.h"


udm::DerivedSequence::DerivedSequence(const udm::IntervalGraph& intervalGraph)
{
    derivedSequence.push_back(intervalGraph);
}

std::vector<udm::IntervalGraph>& udm::DerivedSequence::getDerivedSequence() noexcept
{
    return derivedSequence;
}

void udm::DerivedSequence::setDerivedSequence(const std::vector<udm::IntervalGraph>& derivedSequence) noexcept
{
    this->derivedSequence = derivedSequence;
}


