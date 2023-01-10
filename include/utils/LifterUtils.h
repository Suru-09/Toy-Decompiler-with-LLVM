#ifndef __LIFTER_UTILS__H
#define __LIFTER_UTILS__H

#include <iostream>
#include <memory>

#include "lifter/IArchitectureStrategy.h"
#include "lifter/LifterContext.h"

namespace utils
{

std::unique_ptr<lifter::IArchitectureStrategy> getStrategy(const std::string& testingFile);
std::shared_ptr<lifter::LifterContext> getLifterCtx(const std::string& testingFile);

} // namespace utils



#endif