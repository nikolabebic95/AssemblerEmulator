#include "SymbolData.h"

namespace bnssemulator {

	std::string SymbolData::name() const noexcept {
		return name_;
	}

	std::istream & operator>>(std::istream & is, SymbolData & data) {
		is >> data.name_;
		is >> data.section_index_;
		is >> data.offset_;
		is >> data.local_;

		return is;
	}
}
