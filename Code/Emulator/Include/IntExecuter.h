#ifndef _int_executer_h_
#define _int_executer_h_
#include "Executer.h"

namespace bnssemulator {
	
	/**
	 * \brief Class representing the executer for the int instruction
	 */
	class IntExecuter : public Executer {
	public:
		void execute(InstructionBitField instruction, Context &context) const override;
	};
}

#endif
