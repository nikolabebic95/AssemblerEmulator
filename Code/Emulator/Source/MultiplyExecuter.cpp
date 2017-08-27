#include "MultiplyExecuter.h"

namespace bnssemulator {

	void MultiplyExecuter::execute(Register & dst, const Register & lhs, const Register & rhs) const {
		dst = lhs * rhs;
	}
}