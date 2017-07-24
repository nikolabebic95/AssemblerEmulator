#include "GlobalSymbolToken.h"

namespace bnss {

	GlobalSymbolsToken::GlobalSymbolsToken(std::vector<std::string> symbols, size_t line_number, std::string line) noexcept : Token(line_number, line), symbols_(symbols) {}
}