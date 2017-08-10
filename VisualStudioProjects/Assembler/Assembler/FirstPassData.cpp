#include "FirstPassData.h"
#include "MessageException.h"

namespace bnssassembler {

	void FirstPassData::incLocationCounter(size_t offset) {
		if (section_table_.empty()) {
			throw MessageException("All data must be in sections");
		}

		section_table_.back().incLocationCounter(offset);
	}

	void FirstPassData::insertSymbol(std::string symbol) {
		if (section_table_.empty()) {
			throw MessageException("All labels must be in sections");
		}

		if (symbol_table_.contains(symbol)) {
			throw MessageException("Symbol " + symbol + " is already defined");
		}

		SymbolData symbol_data(symbol, section_table_.size() - 1, section_table_.back().locationCounter(), true);
		symbol_table_ += symbol_data;
	}

	void FirstPassData::insertSection(SectionType type) {
		insertSection(SectionData(type));
	}

	void FirstPassData::insertSection(SectionType type, size_t index) {
		insertSection(SectionData(type, index));
	}

	void FirstPassData::insertSymbolDefinition(SymbolDefinition symbol) {
		if (symbol_definitions_.count(symbol) > 0) {
			throw MessageException("Symbol " + symbol.name() + " is already defined");
		}

		symbol_definitions_.insert(symbol);
	}

	std::unordered_set<SymbolDefinition> FirstPassData::symbolDefinitions() const noexcept {
		return symbol_definitions_;
	}

	void FirstPassData::insertSection(SectionData section_data) {
		section_table_ += section_data;
	}
}
