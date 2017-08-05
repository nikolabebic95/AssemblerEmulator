#include "RelocationRecord.h"

namespace bnss {

	RelocationRecord::RelocationRecord(bool absolute, size_t section_index) noexcept : absolute_(absolute), section_index_(section_index), section_(true) {}
	RelocationRecord::RelocationRecord(bool absolute, std::string symbol_name) noexcept : absolute_(absolute), symbol_name_(symbol_name), section_(false) {}

	void RelocationRecord::offset(size_t offset) noexcept {
		offset_ = offset;
	}

	void RelocationRecord::dataType(DataType data_type) noexcept {
		data_type_ = data_type;
	}

	size_t RelocationRecord::sectionIndex() const noexcept {
		return section_index_;
	}

	std::string RelocationRecord::symbol_name() const noexcept {
		return symbol_name_;
	}

	bool RelocationRecord::section() const noexcept {
		return section_;
	}
}
