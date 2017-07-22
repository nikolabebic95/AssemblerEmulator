#include "MultiplyOperation.h"

namespace bnss {

	bool MultiplyOperation::validate() const noexcept {
		return !containsSymbol();
	}

	int32_t MultiplyOperation::calculate(int32_t lhs, int32_t rhs) const noexcept {
		return lhs * rhs;
	}
}
