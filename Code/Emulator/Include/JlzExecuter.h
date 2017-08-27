#ifndef _jlz_executer_h_
#define _jlz_executer_h_
#include "ConditionalJumpExecuter.h"

namespace bnssemulator {

	/**
	* \brief Class representing the executer for the jlz instruction
	*/
	class JlzExecuter : public ConditionalJumpExecuter {
	protected:
		bool test(bool negative, bool zero, bool overflow, bool carry) const noexcept override;
	};
}

#endif
