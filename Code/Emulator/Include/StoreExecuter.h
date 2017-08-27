#ifndef _store_executer_h_
#define _store_executer_h_
#include "Executer.h"

namespace bnssemulator {
	
	/**
	 * \brief Class representing the executer for the store instruction
	 */
	class StoreExecuter : public Executer {
	public:
		void execute(InstructionBitField instruction, Context &context) const override;
	};
}

#endif
