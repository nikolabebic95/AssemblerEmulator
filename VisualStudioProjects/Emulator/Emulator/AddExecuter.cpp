#include "AddExecuter.h"

namespace bnssemulator {

	void AddExecuter::execute(Register & dst, const Register & lhs, const Register & rhs) const {
		dst = lhs + rhs;
	}
}
