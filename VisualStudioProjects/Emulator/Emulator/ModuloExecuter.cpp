#include "ModuloExecuter.h"

namespace bnssemulator {

	void ModuloExecuter::execute(Register & dst, const Register & lhs, const Register & rhs) const {
		dst = lhs % rhs;
	}
}
