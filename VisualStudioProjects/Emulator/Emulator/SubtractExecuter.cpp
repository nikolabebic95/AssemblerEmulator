#include "SubtractExecuter.h"

namespace bnssemulator {

	void SubtractExecuter::execute(Register & dst, const Register & lhs, const Register & rhs) const {
		dst = lhs - rhs;
	}
}