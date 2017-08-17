#ifndef _jz_executer_h_
#define _jz_executer_h_
#include "ConditionalJumpExecuter.h"

namespace bnssemulator {
	
	/**
	 * \brief Class representing the executer for the jz instruction
	 */
	class JzExecuter : public ConditionalJumpExecuter {
	protected:
		bool test(bool negative, bool zero, bool overflow, bool carry) const noexcept override;
	};
}

#endif
