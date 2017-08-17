#ifndef _asr_executer_h_
#define _asr_executer_h_
#include "AluExecuter.h"

namespace bnssemulator {
	
	/**
	 * \brief Class representing the executer for the asr instruction
	 */
	class AsrExecuter : public AluExecuter {
	protected:
		void execute(Register &dst, const Register &lhs, const Register &rhs) const override;
	};
}

#endif
