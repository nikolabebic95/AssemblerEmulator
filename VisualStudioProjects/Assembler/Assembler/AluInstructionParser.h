#ifndef _alu_instruction_parser_h_
#define _alu_instruction_parser_h_
#include "InstructionParser.h"

namespace bnssassembler {
	
	/**
	 * \brief Class representing the parser for ALU instructions
	 */
	class AluInstructionParser : public InstructionParser {
	public:
		/**
		 * \brief Constructs an AluInstructionParser object
		 */
		AluInstructionParser() noexcept;
	};
}

#endif
