#ifndef _stack_instruction_parser_h_
#define _stack_instruction_parser_h_
#include "InstructionParser.h"

namespace bnssassembler {
	
	/**
	 * \brief Class representing the parser for stack instructions
	 */
	class StackInstructionParser : public InstructionParser {
	public:
		StackInstructionParser() noexcept;
	};
}

#endif
