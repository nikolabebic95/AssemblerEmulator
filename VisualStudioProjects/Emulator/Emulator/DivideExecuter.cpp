#include "DivideExecuter.h"
#include "MessageException.h"

namespace bnssemulator {

	void DivideExecuter::execute(Register & dst, const Register & lhs, const Register & rhs) const{
		if (rhs == 0) {
			throw MessageException("Division by zero");
		}

		dst = lhs / rhs;
	}
}
