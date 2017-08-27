#include "SymbolData.h"

namespace bnssemulator {

	std::string SymbolData::name() const noexcept {
		return name_;
	}

	size_t SymbolData::sectionIndex() const noexcept {
		return section_index_;
	}

	size_t SymbolData::offset() const noexcept {
		return offset_;
	}

	std::istream & operator>>(std::istream & is, SymbolData & data) {
		is >> data.name_;
		is >> data.section_index_;
		is >> data.offset_;
		is >> data.local_;

		return is;
	}
}
