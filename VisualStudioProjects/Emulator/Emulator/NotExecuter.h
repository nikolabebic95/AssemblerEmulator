#ifndef _not_executer_h_
#define _not_executer_h_
#include "Executer.h"

namespace bnssemulator {
	
	/**
	 * \brief Class representing the executer for the not instruction
	 */
	class NotExecuter : public Executer {
	public:
		void execute(InstructionBitField instruction, Context &context) const override;
	};
}

#endif
