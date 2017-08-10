#ifndef _load_instruction_parser_h_
#define _load_instruction_parser_h_
#include "InstructionParser.h"

namespace bnssassembler {
	
	/**
	 * \brief Class representing the load instruction parser
	 */
	class LoadInstructionParser : public InstructionParser {
	public:
		LoadInstructionParser() noexcept;
	};
}

#endif
