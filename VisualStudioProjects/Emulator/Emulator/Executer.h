#ifndef _executer_h_
#define _executer_h_
#include "InstructionBitField.h"
#include "Context.h"

namespace bnssemulator {
	
	/**
	 * \brief Base class used for executing instructions
	 */
	class Executer {
	public:
		/**
		 * \brief Executes the instruction
		 * \param instruction Instruction
		 * \param context Processor context
		 */
		virtual void execute(InstructionBitField instruction, Context &context) const = 0;
		virtual ~Executer() = default;
	};
}

#endif
