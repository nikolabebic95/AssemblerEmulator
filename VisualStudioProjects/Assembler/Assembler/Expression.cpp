#include "Expression.h"

namespace bnss {
	bool Expression::setValue(std::string symbol, std::shared_ptr<Expression> value) noexcept {
		// Default: No value set
		return false;
	}

	bool Expression::validate() const noexcept {
		// Default: Expression valid
		return true;
	}

	bool Expression::containsSymbol() const noexcept {
		// Default: Does not contain symbol
		return false;
	}

	int Expression::symbolCount() const noexcept {
		// Default: Does not contain any symbol
		return 0;
	}

	void Expression::pushChildren(std::stack<std::reference_wrapper<std::shared_ptr<Expression>>> &stack) const noexcept {
		// Default: Do nothing
	}

	void Expression::resolveSymbolTable(const SymbolTable &symbol_table) noexcept {
		// Default: Do nothing
	}

	void Expression::resolveImports(std::unordered_set<std::string> imported_symbols) noexcept {
		// Default: Do nothing
	}

	void Expression::resolveCurrentPcSymbol(size_t section_index, size_t offset) noexcept {
		// Default: Do nothing
	}

	std::list<RelocationRecord> Expression::generateRelocations() const {
		// Default: Return empty list
		return std::list<RelocationRecord>();
	}
}
