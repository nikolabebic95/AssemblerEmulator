#ifndef _immediate_parser_h_
#define _immediate_parser_h_
#include "OperandParser.h"

namespace bnssassembler {
	
	/**
	 * \brief Class representing the parser for the immediate operands
	 */
	class ImmediateParser : public OperandParser {
	protected:
		std::shared_ptr<Operand> parse(std::string str) const override;
	};
}

#endif
