#ifndef _memory_direct_parser_h_
#define _memory_direct_parser_h_
#include "OperandParser.h"

namespace bnss {
	
	/**
	 * \brief Class representing the parser for the memory direct operand
	 */
	class MemoryDirectParser : public OperandParser {
	protected:
		std::shared_ptr<Operand> parse(std::string str) const noexcept override;
	};
}

#endif
