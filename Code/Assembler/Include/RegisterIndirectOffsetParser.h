#ifndef _register_indirect_offset_parser_h_
#define _register_indirect_offset_parser_h_
#include "OperandParser.h"

namespace bnssassembler {
	
	/**
	 * \brief Class representing the parser for the register indirect operand with offset
	 */
	class RegisterIndirectOffsetParser : public OperandParser {
	protected:
		std::shared_ptr<Operand> parse(std::string str) const override;
	};
}

#endif
