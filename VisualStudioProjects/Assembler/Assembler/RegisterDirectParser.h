#ifndef _register_direct_parser_h_
#define _register_direct_parser_h_
#include "OperandParser.h"

namespace bnssassembler {
	
	/**
	 * \brief Class representing the parser for the register direct operand
	 */
	class RegisterDirectParser : public OperandParser {
	protected:
		std::shared_ptr<Operand> parse(std::string str) const override;
	};
}

#endif
