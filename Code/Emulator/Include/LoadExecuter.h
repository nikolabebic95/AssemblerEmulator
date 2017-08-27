#ifndef _load_executer_h_
#define _load_executer_h_
#include "Executer.h"

namespace bnssemulator {

	/**
	* \brief Class representing the executer for the load instruction
	*/
	class LoadExecuter : public Executer {
	public:
		void execute(InstructionBitField instruction, Context &context) const override;
	};
}

#endif
