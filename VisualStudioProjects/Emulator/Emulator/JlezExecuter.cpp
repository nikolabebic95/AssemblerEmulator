#include "JlezExecuter.h"

namespace bnssemulator {

	bool JlezExecuter::test(bool negative, bool zero, bool overflow, bool carry) const noexcept {
		return negative != overflow;
	}
}
