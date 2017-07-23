#ifndef _symbol_definition_token_h_
#define _symbol_definition_token_h_
#include "Token.h"
#include "MicroRiscExpression.h"

namespace bnss {
	
	/**
	 * \brief Class representing the symbol definition token
	 */
	class SymbolDefinitionToken : public Token {
	public:
		SymbolDefinitionToken(std::string name, MicroRiscExpression value, size_t line_number, std::string line) noexcept;
	private:
		std::string name_;
		MicroRiscExpression value_;
	};
}

#endif
