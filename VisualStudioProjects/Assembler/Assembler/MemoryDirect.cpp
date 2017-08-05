#include "MemoryDirect.h"

namespace bnss {

	MemoryDirect::MemoryDirect(MicroRiscExpression address) noexcept : address_(address) {}

	void MemoryDirect::packToInstruction(InstructionBitFieldUnion &instruction, uint32_t &second_word, std::list<RelocationRecord> &relocations) const {
		instruction.bit_field.address_mode = MEMORY_DIRECT;
		second_word = address_.value();
		relocations.splice(relocations.end(), address_.generateRelocations());
	}

	void MemoryDirect::resolveSymbols(std::unordered_set<SymbolDefinition> symbols) noexcept {
		for (auto &symbol : symbols) {
			address_.setValue(symbol.name(), symbol.expression());
		}
	}

	void MemoryDirect::resolveSymbolTable(const SymbolTable &symbol_table) noexcept {
		address_.resolveSymbolTable(symbol_table);
	}

	void MemoryDirect::resolveImports(std::unordered_set<std::string> imported_symbols) noexcept {
		address_.resolveImports(imported_symbols);
	}

	AddressMode MemoryDirect::addressMode() const noexcept {
		return MEMORY_DIRECT;
	}
}
