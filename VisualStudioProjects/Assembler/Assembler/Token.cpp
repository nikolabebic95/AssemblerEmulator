#include "Token.h"

namespace bnss {

	Token::Token(size_t line_number, std::string line) noexcept : line_number_(line_number), line_(line) {}
	
	void Token::resolveSymbolDefinitions(std::unordered_set<SymbolDefinition> symbols) noexcept {
		// Default: Do nothing
	}

	bool Token::usesAddress() const noexcept {
		// Default: Do not use address
		return false;
	}

	void Token::resolveSymbolTable(const SymbolTable &symbol_table) noexcept {
		// Default: Do nothing
	}

	void Token::resolveImports(std::unordered_set<std::string> imported_symbols) noexcept {
		// Default: Do nothing
	}

	size_t Token::lineNumber() const noexcept {
		return line_number_;
	}

	std::string Token::line() const noexcept {
		return line_;
	}
}
