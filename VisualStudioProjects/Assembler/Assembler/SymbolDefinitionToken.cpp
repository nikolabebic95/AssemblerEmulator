#include "SymbolDefinitionToken.h"

namespace bnss {

	SymbolDefinitionToken::SymbolDefinitionToken(std::string name, MicroRiscExpression value, size_t line_number, std::string line) noexcept : Token(line_number, line), name_(name), value_(value) {}
}
