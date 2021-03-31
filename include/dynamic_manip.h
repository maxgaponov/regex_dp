#pragma once
#include <dynamic.h>

DynamicState sum(const DynamicState& lhs, const DynamicState& rhs);
DynamicState concat(const DynamicState& lhs, const DynamicState& rhs);
DynamicState iteration(const DynamicState& ds);
