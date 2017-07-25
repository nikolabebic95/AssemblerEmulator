#include "Token.h"

namespace bnss {

	Token::Token(size_t line_number, std::string line) noexcept : line_number_(line_number), line_(line) {}
	
	void Token::resolveSymbolDefinitions(std::unordered_set<SymbolDefinition> symbols) noexcept {
		// Default: Do nothing
	}

	size_t Token::lineNumber() const noexcept {
		return line_number_;
	}

	std::string Token::line() const noexcept {
		return line_;
	}
}
