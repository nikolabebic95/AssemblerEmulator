#include "RelocationRecord.h"

namespace bnssemulator {

	std::istream &operator>>(std::istream & is, RelocationRecord & data) {
		is >> data.offset_;
		is >> data.absolute_;
		is >> data.section_;
		if (data.section_) {
			is >> data.section_index_;
		}
		else {
			is >> data.symbol_name_;
		}

		return is;
	}

	size_t RelocationRecord::offset() const noexcept {
		return offset_;
	}

	bool RelocationRecord::absolute() const noexcept {
		return absolute_;
	}

	size_t RelocationRecord::sectionIndex() const noexcept {
		return section_index_;
	}

	std::string RelocationRecord::symbolName() const noexcept {
		return symbol_name_;
	}

	bool RelocationRecord::section() const noexcept {
		return section_;
	}

}