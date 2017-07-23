#ifndef _register_indirect_parser_h_
#define _register_indirect_parser_h_
#include "OperandParser.h"

namespace bnss {
	
	/**
	 * \brief Class representing the parser for the register indirect operand
	 */
	class RegisterIndirectParser : public OperandParser {
	protected:
		std::shared_ptr<Operand> parse(std::string str) const override;
	};
}

#endif
