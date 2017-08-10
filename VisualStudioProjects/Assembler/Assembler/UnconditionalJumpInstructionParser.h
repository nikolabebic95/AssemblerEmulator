#ifndef _unconditional_jump_instruction_parser_h_
#define _unconditional_jump_instruction_parser_h_
#include "InstructionParser.h"

namespace bnssassembler {
	
	class UndonditionalJumpInstructionParser : public InstructionParser {
	public:
		UndonditionalJumpInstructionParser() noexcept;
	};
}

#endif
