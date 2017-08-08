#include "Operand.h"
#include <unordered_set>

namespace bnss {

	void Operand::resolveSymbols(std::unordered_set<SymbolDefinition> symbols) noexcept {
		// Default: Do nothing
	}

	void Operand::resolveSymbolTable(const SymbolTable &symbol_table) noexcept {
		// Default: Do nothing
	}

	void Operand::resolveImports(std::unordered_set<std::string> imported_symbols) noexcept {
		// Default: Do nothing
	}

	void Operand::resolveCurrentPcSymbol(size_t section_index, size_t offset) noexcept {
		// Default: Do nothing
	}
}
