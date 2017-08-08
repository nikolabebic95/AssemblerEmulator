#include "RegisterIndirectOffset.h"
#include "MessageException.h"

namespace bnss {

	RegisterIndirectOffset::RegisterIndirectOffset(Register reg, MicroRiscExpression offset_or_address, bool absolute) : reg_(reg), offset_or_address_(offset_or_address), absolute_(absolute) {
		if (absolute && reg != PC) {
			throw MessageException("Only PC relative address can be absolute");
		}
	}

	void RegisterIndirectOffset::packToInstruction(InstructionBitFieldUnion &instruction, uint32_t &second_word, std::list<RelocationRecord> &relocations) const {
		instruction.bit_field.address_mode = REGISTER_INDIRECT_OFFSET;
		second_word = offset_or_address_.value();
		if (absolute_) {
			second_word += pc_offset_ + 4;
			auto rels = offset_or_address_.generateRelocations();
			if (rels.empty()) {
				throw MessageException("PC Relative address must contain at least one label");
			}

			auto found_same_section = false;

			for (auto &rel : rels) {
				if (rel.sectionIndex() == pc_section_index_) {
					found_same_section = true;
					second_word -= (pc_offset_ + 4) * 2;
					rels.remove(rel);
					break;
				}
			}

			if (!found_same_section) {
				rels.front().absolute(false);
			}

			relocations.splice(relocations.end(), rels);
		}
		else {
			relocations.splice(relocations.end(), offset_or_address_.generateRelocations());
		}
		
		if (instruction.bit_field.register0 == NONE) {
			instruction.bit_field.register0 = reg_;
			return;
		}

		if (instruction.bit_field.register1 == NONE) {
			instruction.bit_field.register1 = reg_;
			return;
		}

		if (instruction.bit_field.register2 == NONE) {
			instruction.bit_field.register2 = reg_;
		}
	}

	void RegisterIndirectOffset::resolveSymbols(std::unordered_set<SymbolDefinition> symbols) noexcept {
		for (auto &symbol : symbols) {
			offset_or_address_.setValue(symbol.name(), symbol.expression());
		}
	}

	void RegisterIndirectOffset::resolveSymbolTable(const SymbolTable &symbol_table) noexcept {
		offset_or_address_.resolveSymbolTable(symbol_table);
	}

	void RegisterIndirectOffset::resolveImports(std::unordered_set<std::string> imported_symbols) noexcept {
		offset_or_address_.resolveImports(imported_symbols);
	}

	void RegisterIndirectOffset::resolveCurrentPcSymbol(size_t section_index, size_t offset) noexcept {
		offset_or_address_.resolveCurrentPcSymbol(section_index, offset);
		pc_section_index_ = section_index;
		pc_offset_ = offset;
	}

	AddressMode RegisterIndirectOffset::addressMode() const noexcept {
		return REGISTER_INDIRECT_OFFSET;
	}
}
