#ifndef _interrupt_instruction_parser_h_
#define _interrupt_instruction_parser_h_
#include "InstructionParser.h"

namespace bnss {
	
	class InterruptInstructionParser : public InstructionParser {
	public:
		InterruptInstructionParser() noexcept;
	};
}

#endif
