#include "SecondPassData.h"
#include "StringHelper.h"
#include <iostream>
#include "PrintHelpers.h"

namespace bnss {

	SecondPassData::SecondPassData(FirstPassData &&first_pass_data) noexcept : symbol_table_(move(first_pass_data.symbol_table_)), section_table_(move(first_pass_data.section_table_)) {}

	void SecondPassData::nextSection() noexcept {
		section_table_.nextSection();
		if (org_valid_) {
			org_valid_ = false;
			section_table_.current().org(org_address_);
		}
	}

	bool SecondPassData::orgValid() const noexcept {
		return org_valid_;
	}

	bool SecondPassData::contains(std::string symbol) const noexcept {
		return symbol_table_.contains(symbol);
	}

	void SecondPassData::insertImported(std::string symbol) {
		imported_symbols_.insert(symbol);
	}

	void SecondPassData::exportSymbol(std::string symbol) {
		symbol_table_.exportSymbol(symbol);
	}

	SectionType SecondPassData::currentSectionType() const noexcept {
		return section_table_.currentSectionType();
	}

	void SecondPassData::addData(uint8_t data, std::list<RelocationRecord> relocations) {
		section_table_.addData(data, relocations);
	}

	void SecondPassData::addData(uint16_t data, std::list<RelocationRecord> relocations) {
		section_table_.addData(data, relocations);
	}

	void SecondPassData::addData(uint32_t data, std::list<RelocationRecord> relocations) {
		section_table_.addData(data, relocations);
	}

	void SecondPassData::org(uint32_t address) {
		org_address_ = address;
		org_valid_ = true;
	}

	SymbolTable & SecondPassData::symbolTable() noexcept {
		return symbol_table_;
	}

	const SymbolTable & SecondPassData::symbolTable() const noexcept {
		return const_cast<SecondPassData &>(*this).symbolTable();
	}

	std::unordered_set<std::string> &SecondPassData::importedSymbols() {
		return imported_symbols_;
	}

	const std::unordered_set<std::string> &SecondPassData::importedSymbols() const {
		return const_cast<SecondPassData &>(*this).importedSymbols();
	}

	size_t SecondPassData::currentSectionIndex() const noexcept {
		return section_table_.currentIndex();
	}

	size_t SecondPassData::currentSectionOffset() const noexcept {
		if (currentSectionIndex() == static_cast<size_t>(-1)) {
			return 0;
		}

		return section_table_.current().size();
	}

	std::ostream & operator<<(std::ostream &os, const SecondPassData &data) {
		os << data.imported_symbols_.size() << std::endl;

		std::cout << UPPER_LEFT << multiple(HORIZONTAL, 81) << UPPER_RIGHT << std::endl;
		std::cout << VERTICAL << UPPER_LEFT << multiple(HORIZONTAL, 79) << UPPER_RIGHT << VERTICAL << std::endl;
		std::cout << VERTICAL << VERTICAL << std::setw(79) << std::left << " Imported symbols:" << VERTICAL << VERTICAL << std::endl;
		std::cout << VERTICAL << LOWER_LEFT << multiple(HORIZONTAL, 79) << LOWER_RIGHT << VERTICAL << std::endl;
		std::cout << T_RIGHT << multiple(HORIZONTAL, 81) << T_LEFT << std::endl;

		for (auto &symbol : data.imported_symbols_) {
			os << symbol << std::endl;
			std::cout << VERTICAL << " " << std::setw(80) << std::left << symbol << VERTICAL << std::endl;
		}

		std::cout << LOWER_LEFT << multiple(HORIZONTAL, 81) << LOWER_RIGHT << std::endl << std::endl << std::endl;
		os << data.section_table_ << std::endl;
		os << data.symbol_table_ << std::endl;
		
		return os;
	}
}
