#include "RelocationRecord.h"
#include <iostream>
#include <iomanip>
#include "PrintHelpers.h"

namespace bnssassembler {

	RelocationRecord::RelocationRecord(bool absolute, size_t section_index) noexcept : absolute_(absolute), section_index_(section_index), section_(true) {}
	RelocationRecord::RelocationRecord(bool absolute, std::string symbol_name) noexcept : absolute_(absolute), symbol_name_(symbol_name), section_(false) {}

	void RelocationRecord::offset(size_t offset) noexcept {
		offset_ = offset;
	}

	void RelocationRecord::dataType(DataType data_type) noexcept {
		data_type_ = data_type;
	}

	void RelocationRecord::absolute(bool absolute) noexcept {
		absolute_ = absolute;
	}

	void RelocationRecord::toggleOpposite() noexcept {
		opposite_ = !opposite_;
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

	bool RelocationRecord::opposite() const noexcept {
		return opposite_;
	}

	std::ostream & operator<<(std::ostream &os, const RelocationRecord &record) {
		os << record.offset_ << std::endl;
		os << record.absolute_ << std::endl;
		os << record.section_ << std::endl;
		if (record.section_) {
			os << record.section_index_ << std::endl;
		}
		else {
			os << record.symbol_name_ << std::endl;
		}

		os << record.data_type_ << std::endl;

		std::cout << VERTICAL << " " << std::setw(7) << std::left << record.offset_ << VERTICAL << " " << (record.absolute_ ? "Absolute" : "Relative") << " " << VERTICAL << " ";
		if (record.section_) {
			std::cout << std::setw(8) << std::left << std::to_string(record.section_index_) + "." << VERTICAL << std::setw(51) << " " << VERTICAL << std::endl;
		}
		else {
			std::cout << std::setw(8) << " " << VERTICAL << std::setw(51) << std::left << record.symbol_name_ << VERTICAL << std::endl;
		}

		return os;
	}

	bool operator==(const RelocationRecord &lhs, const RelocationRecord &rhs) {
		return
			lhs.offset_ == rhs.offset_ &&
			lhs.absolute_ == rhs.absolute_ &&
			lhs.section_ == rhs.section_ &&
			(lhs.section_ ? lhs.section_index_ == rhs.section_index_ : lhs.symbol_name_ == rhs.symbol_name_) &&
			lhs.data_type_ == rhs.data_type_;
	}

	bool operator!=(const RelocationRecord &lhs, const RelocationRecord &rhs) {
		return !(lhs == rhs);
	}
}
