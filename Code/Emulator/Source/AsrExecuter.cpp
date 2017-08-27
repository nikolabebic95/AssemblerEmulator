#include "AsrExecuter.h"

namespace bnssemulator {

	void AsrExecuter::execute(Register & dst, const Register & lhs, const Register & rhs) const {
		dst = lhs >> rhs;
	}
}
