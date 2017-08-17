#ifndef _or_executer_h_
#define _or_executer_h_
#include "AluExecuter.h"

namespace bnssemulator {
	
	/**
	 * \brief Class representing the executer for the or instruction
	 */
	class OrExecuter : public AluExecuter {
	protected:
		void execute(Register &dst, const Register &lhs, const Register &rhs) const override;
	};
}

#endif
