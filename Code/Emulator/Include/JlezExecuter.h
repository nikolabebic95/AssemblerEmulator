#ifndef _jlez_executer_h_
#define _jlez_executer_h_
#include "ConditionalJumpExecuter.h"

namespace bnssemulator {

	/**
	* \brief Class representing the executer for the jlez instruction
	*/
	class JlezExecuter : public ConditionalJumpExecuter {
	protected:
		bool test(bool negative, bool zero, bool overflow, bool carry) const noexcept override;
	};
}

#endif
