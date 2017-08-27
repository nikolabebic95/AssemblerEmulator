#include "JlzExecuter.h"

namespace bnssemulator {

	bool JlzExecuter::test(bool negative, bool zero, bool overflow, bool carry) const noexcept {
		return (negative != overflow) && !zero;
	}
}
