#ifndef _interrupt_instruction_parser_h_
#define _interrupt_instruction_parser_h_
#include "InstructionParser.h"

namespace bnssassembler {
	
	/**
	 * \brief Class representing the parser for the interrupt instruction
	 */
	class InterruptInstructionParser : public InstructionParser {
	public:
		/**
		 * \brief Constructs an InterruptInstructionParser object
		 */
		InterruptInstructionParser() noexcept;
	};
}

#endif
