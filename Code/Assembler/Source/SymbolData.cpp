#include "SymbolData.h"
#include <iostream>
#include "PrintHelpers.h"
#include <iomanip>

namespace bnssassembler {

	SymbolData::SymbolData(std::string name, size_t section_index, size_t offset, bool local) noexcept : name_(name), section_index_(section_index), offset_(offset), local_(local) {}

	std::string SymbolData::name() const noexcept {
		return name_;
	}

	size_t SymbolData::sectionIndex() const noexcept {
		return section_index_;
	}

	size_t SymbolData::offset() const noexcept {
		return offset_;
	}

	bool SymbolData::local() const noexcept {
		return local_;
	}

	void SymbolData::exportSymbol() noexcept {
		local_ = false;
	}

	std::ostream & operator<<(std::ostream &os, const SymbolData &data) {
		os << data.name_ << std::endl;
		os << data.section_index_ << std::endl;
		os << data.offset_ << std::endl;
		os << data.local_ << std::endl;

		std::cout << VERTICAL << " " << std::setw(46) << std::left << data.name_ << VERTICAL << " " << std::setw(8) << std::left << data.section_index_ << VERTICAL << " " << std::setw(7) << std::left << data.offset_ << VERTICAL << std::setw(14) << std::left << (data.local_ ? " Local" : " Global") << VERTICAL << std::endl;

		return os;
	}
}
