#ifndef _pop_executer_h_
#define _pop_executer_h_
#include "Executer.h"

namespace bnssemulator {
	
	/**
	 * \brief Class representing the executer for the pop instruction
	 */
	class PopExecuter : public Executer {
	public:
		void execute(InstructionBitField instruction, Context &context) const override;
	};
}

#endif
