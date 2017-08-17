#include "XorExecuter.h"

namespace bnssemulator {

	void XorExecuter::execute(Register & dst, const Register & lhs, const Register & rhs) const {
		dst = lhs ^ rhs;
	}
}
