#include "Immediate.h"

namespace bnss {

	Immediate::Immediate(MicroRiscExpression value) noexcept : value_(value) {}

	void Immediate::packToInstruction(InstructionBitFieldUnion &instruction, uint32_t &second_word, std::list<RelocationRecord> &relocations) const {
		instruction.bit_field.address_mode = IMMEDIATE;
		second_word = value_.value();
		relocations.splice(relocations.end(), value_.generateRelocations());
	}

	void Immediate::resolveSymbols(std::unordered_set<SymbolDefinition> symbols) noexcept {
		for (auto &symbol : symbols) {
			value_.setValue(symbol.name(), symbol.expression());
		}
	}

	void Immediate::resolveSymbolTable(const SymbolTable &symbol_table) noexcept {
		value_.resolveSymbolTable(symbol_table);
	}

	void Immediate::resolveImports(std::unordered_set<std::string> imported_symbols) noexcept {
		value_.resolveImports(imported_symbols);
	}

	void Immediate::resolveCurrentPcSymbol(size_t section_index, size_t offset) noexcept {
		value_.resolveCurrentPcSymbol(section_index, offset);
	}

	AddressMode Immediate::addressMode() const noexcept {
		return IMMEDIATE;
	}
}
