#include "AssemblerOutput.h"
#include <string>
#include "MessageException.h"

namespace bnssemulator {

	std::istream & operator>>(std::istream & is, AssemblerOutput & data) {
		size_t num_of_imported_symbols;
		is >> num_of_imported_symbols;
		for (size_t i = 0; i < num_of_imported_symbols; i++) {
			std::string symbol;
			is >> symbol;
			data.imported_symbols_.insert(symbol);
		}

		size_t section_table_size;
		is >> section_table_size;
		for (size_t i = 0; i < section_table_size; i++) {
			SectionData section;
			is >> section;
			data.section_table_.push_back(section);
		}

		size_t symbol_table_size;
		is >> symbol_table_size;
		for (size_t i = 0; i < symbol_table_size; i++) {
			SymbolData symbol;
			is >> symbol;
			data.symbol_table_[symbol.name()] = symbol;
		}
		
		return is;
	}
	
	std::vector<SectionData> & AssemblerOutput::sectionTable() noexcept {
		return section_table_;
	}

	const std::vector<SectionData> & AssemblerOutput::sectionTable() const noexcept {
		return const_cast<AssemblerOutput &>(*this).sectionTable();
	}

	std::unordered_map<std::string, SymbolData> & AssemblerOutput::symbolTable() noexcept {
		return symbol_table_;
	}

	const std::unordered_map<std::string, SymbolData> & AssemblerOutput::symbolTable() const noexcept {
		return const_cast<AssemblerOutput &>(*this).symbolTable();
	}

	bool AssemblerOutput::importedSymbolsExist() const noexcept {
		return imported_symbols_.size() != 0;
	}

	std::vector<std::string> AssemblerOutput::importedSymbolsAsVector() const noexcept {
		std::vector<std::string> ret;
		for (auto &symbol : imported_symbols_) {
			ret.push_back(symbol);
		}

		return ret;
	}

	uint32_t AssemblerOutput::startOfProgram(std::string start_symbol) const {
		if (symbol_table_.count(start_symbol) == 0) {
			throw MessageException("The " + start_symbol + " symbol is not defined");
		}

		auto symbol = symbol_table_.at(start_symbol);
		return section_table_[symbol.sectionIndex()].address() + symbol.offset();
	}
}
