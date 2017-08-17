#ifndef _modulo_executer_h_
#define _modulo_executer_h_
#include "AluExecuter.h"

namespace bnssemulator {
	
	/**
	 * \brief Class representing the executer for the modulo instruction
	 */
	class ModuloExecuter : public AluExecuter {
	protected:
		void execute(Register &dst, const Register &lhs, const Register &rhs) const override;
	};
}

#endif
