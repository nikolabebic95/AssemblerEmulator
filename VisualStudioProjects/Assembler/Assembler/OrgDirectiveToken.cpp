#include "OrgDirectiveToken.h"
#include "MessageException.h"
#include "SecondPassData.h"

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

	void OrgDirectiveToken::secondPass(SecondPassData &data) const {
		if (!expression_.generateRelocations().empty()) {
			throw MessageException("ORG directive expression can not have labels");
		}

		data.org(static_cast<uint32_t>(expression_.value()));
	}

	void OrgDirectiveToken::resolveSymbolTable(const SymbolTable &symbol_table) noexcept {
		expression_.resolveSymbolTable(symbol_table);
	}

	void OrgDirectiveToken::resolveImports(std::unordered_set<std::string> imported_symbols) noexcept {
		expression_.resolveImports(imported_symbols);
	}
}
