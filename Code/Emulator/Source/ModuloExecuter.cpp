#include "ModuloExecuter.h"
#include "MessageException.h"

namespace bnssemulator {

	void ModuloExecuter::execute(Register & dst, const Register & lhs, const Register & rhs) const {
		if (rhs == 0) {
			throw MessageException("Modulo by zero");
		}

		dst = lhs % rhs;
	}
}
