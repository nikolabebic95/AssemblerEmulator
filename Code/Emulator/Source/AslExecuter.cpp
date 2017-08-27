#include "AslExecuter.h"

namespace bnssemulator {

	void AslExecuter::execute(Register & dst, const Register & lhs, const Register & rhs) const {
		dst = lhs << rhs;
	}
}