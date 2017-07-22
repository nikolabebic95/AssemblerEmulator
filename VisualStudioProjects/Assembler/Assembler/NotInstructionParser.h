#ifndef _not_instruction_parser_h_
#define _not_instruction_parser_h_
#include "InstructionParser.h"

namespace bnss {
	
	/**
	 * \brief Class representing the parser for the not instruction
	 */
	class NotInstructionParser : public InstructionParser {
	public:
		NotInstructionParser() noexcept;
	};
}

#endif
