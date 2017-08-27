#ifndef _not_instruction_parser_h_
#define _not_instruction_parser_h_
#include "InstructionParser.h"

namespace bnssassembler {
	
	/**
	 * \brief Class representing the parser for the not instruction
	 */
	class NotInstructionParser : public InstructionParser {
	public:
		/**
		 * \brief Constructs a NotInstructionParser object
		 */
		NotInstructionParser() noexcept;
	};
}

#endif
