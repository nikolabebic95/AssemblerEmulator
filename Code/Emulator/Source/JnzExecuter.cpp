#include "JnzExecuter.h"

namespace bnssemulator {

	bool JnzExecuter::test(bool negative, bool zero, bool overflow, bool carry) const noexcept {
		return !zero;
	}
}
