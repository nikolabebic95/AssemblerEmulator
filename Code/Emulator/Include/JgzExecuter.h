#ifndef _jgz_executer_h_
#define _jgz_executer_h_
#include "ConditionalJumpExecuter.h"

namespace bnssemulator {

	/**
	* \brief Class representing the executer for the jgz instruction
	*/
	class JgzExecuter : public ConditionalJumpExecuter {
	protected:
		bool test(bool negative, bool zero, bool overflow, bool carry) const noexcept override;
	};
}

#endif
