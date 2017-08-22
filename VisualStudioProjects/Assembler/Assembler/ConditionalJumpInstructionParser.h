#ifndef _conditional_jump_instruction_parser_h_
#define _conditional_jump_instruction_parser_h_
#include "InstructionParser.h"

namespace bnssassembler {
	
	/**
	 * \brief Class representing the parser for conditional jump instructions
	 */
	class ConditionalJumpInstructionParser : public InstructionParser {
	public:
		/**
		 * \brief Constructs a ConditionalJumpInstructionParser object
		 */
		ConditionalJumpInstructionParser() noexcept;
	};
}

#endif
