#include "JgzExecuter.h"

namespace bnssemulator {

	bool JgzExecuter::test(bool negative, bool zero, bool overflow, bool carry) const noexcept {
		return (negative == overflow) && !zero;
	}
}
