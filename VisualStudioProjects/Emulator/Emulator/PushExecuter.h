#ifndef _push_executer_h_
#define _push_executer_h_
#include "Executer.h"

namespace bnssemulator {
	
	/**
	 * \brief Class representing the executer for the push instruction
	 */
	class PushExecuter : public Executer {
	public:
		void execute(InstructionBitField instruction, Context &context) const override;
	};
}

#endif
