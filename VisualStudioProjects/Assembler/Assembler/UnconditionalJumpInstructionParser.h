#ifndef _unconditional_jump_instruction_parser_h_
#define _unconditional_jump_instruction_parser_h_
#include "InstructionParser.h"

namespace bnssassembler {
	
	/**
	 * \brief Class representing the parser for the unconditional jump instructions
	 */
	class UndonditionalJumpInstructionParser : public InstructionParser {
	public:
		/**
		 * \brief Constructs an UnconditionalJumpInstructionParser object
		 */
		UndonditionalJumpInstructionParser() noexcept;
	};
}

#endif
