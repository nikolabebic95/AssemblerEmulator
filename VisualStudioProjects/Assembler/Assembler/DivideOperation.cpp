#include "DivideOperation.h"
#include "DivisionByZeroException.h"

namespace bnssassembler {

	bool DivideOperation::validate() const noexcept {
		return !containsSymbol();
	}

	int32_t DivideOperation::calculate(int32_t lhs, int32_t rhs) const {
		if (rhs == 0) {
			throw DivisionByZeroException();
		}

		return lhs / rhs;
	}
}
