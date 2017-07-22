#include "AddOperation.h"

namespace bnss {

	int32_t AddOperation::calculate(int32_t lhs, int32_t rhs) const noexcept {
		return lhs + rhs;
	}
}
