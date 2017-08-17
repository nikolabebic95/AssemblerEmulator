#include "JgezExecuter.h"

namespace bnssemulator {

	bool JgezExecuter::test(bool negative, bool zero, bool overflow, bool carry) const noexcept {
		return negative == overflow;
	}
}
