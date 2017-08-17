#ifndef _subtract_executer_h_
#define _subtract_executer_h_
#include "AluExecuter.h"

namespace bnssemulator {
	
	/**
	 * \brief Class representing the executer for the subtract instruction
	 */
	class SubtractExecuter : public AluExecuter {
	protected:
		void execute(Register &dst, const Register &lhs, const Register &rhs) const override;
	};
}

#endif
