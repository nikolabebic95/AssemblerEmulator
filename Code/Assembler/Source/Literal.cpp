#include "Literal.h"

namespace bnssassembler {

	Literal::Literal(int32_t value) noexcept : value_(value) {}

	int32_t Literal::value() const {
		return value_;
	}
}
