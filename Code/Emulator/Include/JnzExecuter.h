#ifndef _jnz_executer_h_
#define _jnz_executer_h_
#include "ConditionalJumpExecuter.h"

namespace bnssemulator {
	
	/**
	 * \brief Class representing the executer for the jnz instruction
	 */
	class JnzExecuter : public ConditionalJumpExecuter {
	protected:
		bool test(bool negative, bool zero, bool overflow, bool carry) const noexcept override;
	};
}

#endif
