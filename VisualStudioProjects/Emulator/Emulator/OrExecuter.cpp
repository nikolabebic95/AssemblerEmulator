#include "OrExecuter.h"

namespace bnssemulator {

	void OrExecuter::execute(Register & dst, const Register & lhs, const Register & rhs) const {
		dst = lhs | rhs;
	}
}