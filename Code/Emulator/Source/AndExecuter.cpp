#include "AndExecuter.h"

namespace bnssemulator {

	void AndExecuter::execute(Register & dst, const Register & lhs, const Register & rhs) const {
		dst = lhs & rhs;
	}
}
