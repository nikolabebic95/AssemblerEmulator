#include "SubtractOperation.h"

namespace bnss {

	bool SubtractOperation::containsSymbol() const noexcept {
		if (Operation::containsSymbol()) {
			return symbolCount() == 0;
		}

		return false;
	}

	int SubtractOperation::symbolCount() const noexcept {
		return left()->symbolCount() - right()->symbolCount();
	}

	int32_t SubtractOperation::calculate(int32_t lhs, int32_t rhs) const noexcept {
		return lhs - rhs;
	}
}