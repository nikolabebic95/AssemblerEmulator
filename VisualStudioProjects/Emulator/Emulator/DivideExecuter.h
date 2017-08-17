#ifndef _divide_executer_h_
#define _divide_executer_h_
#include "AluExecuter.h"

namespace bnssemulator {
	
	/**
	 * \brief Class representing the executer of the divide instruction
	 */
	class DivideExecuter : public AluExecuter {
	protected:
		void execute(Register &dst, const Register &lhs, const Register &rhs) const override;
	};
}

#endif
