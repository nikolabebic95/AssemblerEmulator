#ifndef _store_instruction_parser_h_
#define _store_instruction_parser_h_
#include "InstructionParser.h"

namespace bnssassembler {
	
	/**
	 * \brief Class representing the parser for the store instruction
	 */
	class StoreInstructionParser : public InstructionParser {
	public:
		/**
		 * \brief Constructs a StoreInstructionParser object
		 */
		StoreInstructionParser() noexcept;
	};
}

#endif
