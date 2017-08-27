#ifndef _jgez_executer_h_
#define _jgez_executer_h_
#include "ConditionalJumpExecuter.h"

namespace bnssemulator {

	/**
	* \brief Class representing the executer for the jgez instruction
	*/
	class JgezExecuter : public ConditionalJumpExecuter {
	protected:
		bool test(bool negative, bool zero, bool overflow, bool carry) const noexcept override;
	};
}

#endif
