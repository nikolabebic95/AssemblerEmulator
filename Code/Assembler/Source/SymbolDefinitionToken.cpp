#include "SymbolDefinitionToken.h"

namespace bnssassembler {

	SymbolDefinitionToken::SymbolDefinitionToken(std::string name, MicroRiscExpression value, size_t line_number, std::string line) noexcept : Token(line_number, line), name_(name), value_(value) {}

	void SymbolDefinitionToken::resolveSymbolDefinitions(std::unordered_set<SymbolDefinition> symbols) noexcept {
		for (auto &symbol : symbols) {
			value_.setValue(symbol.name(), symbol.expression());
		}
	}

	void SymbolDefinitionToken::firstPass(FirstPassData &data) const {
		data.insertSymbolDefinition(SymbolDefinition(name_, value_));
	}

	void SymbolDefinitionToken::secondPass(SecondPassData &data) const {
		// TODO: Implementation
	}
}
