#include "Literal.h"

namespace bnss {

	Literal::Literal(int32_t value) noexcept : value_(value) {}

	int32_t Literal::value() const {
		return value_;
	}
}
