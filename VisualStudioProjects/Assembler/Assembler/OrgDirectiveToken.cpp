#include "OrgDirectiveToken.h"

namespace bnss {

	OrgDirectiveToken::OrgDirectiveToken(MicroRiscExpression expression, size_t line_number, std::string line) noexcept : Token(line_number, line), expression_(expression) {}

	void OrgDirectiveToken::resolveSymbolDefinitions(std::unordered_set<SymbolDefinition> symbols) noexcept {
		for (auto &symbol : symbols) {
			expression_.setValue(symbol.name(), symbol.expression());
		}
	}

	void OrgDirectiveToken::firstPass(FirstPassData &data) const {
		// Do nothing
	}
}
