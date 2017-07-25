#include "SectionData.h"

namespace bnss {

	SectionData::SectionData(SectionType type) noexcept : type_(type) {}
	SectionData::SectionData(SectionType type, size_t index) noexcept : type_(type), indexed_(true), index_(index) {}

	void SectionData::incLocationCounter(size_t offset) noexcept {
		location_counter_ += offset;
	}

	SectionType SectionData::type() const noexcept {
		return type_;
	}

	bool SectionData::indexed() const noexcept {
		return indexed_;
	}

	size_t SectionData::index() const noexcept {
		return index_;
	}

	size_t SectionData::locationCounter() const noexcept {
		return location_counter_;
	}

	size_t SectionData::hash() const noexcept {
		if (indexed_) {
			return 4 + index_ * 4 + type_;
		}
		
		return type_;
	}

	bool operator==(const SectionData & lhs, const SectionData & rhs) noexcept {
		return lhs.type_ == rhs.type_ && lhs.indexed_ == rhs.indexed_ && (lhs.indexed_ ? lhs.index_ == rhs.index_ : true);
	}

	bool operator!=(const SectionData &lhs, const SectionData &rhs) noexcept {
		return !(lhs == rhs);
	}

	bool operator<(const SectionData &lhs, const SectionData &rhs) noexcept {
		if (lhs.type_ < rhs.type_) {
			return true;
		}

		if (lhs.type_ > rhs.type_) {
			return false;
		}

		if (!lhs.indexed_ && rhs.indexed_) {
			return true;
		}

		if (lhs.indexed_ && !rhs.indexed_) {
			return false;
		}

		if (lhs.indexed_) {
			return lhs.index_ < rhs.index_;
		}

		return false;
	}

	bool operator>(const SectionData &lhs, const SectionData &rhs) noexcept {
		return !(lhs < rhs || lhs == rhs);
	}

	bool operator<=(const SectionData &lhs, const SectionData &rhs) noexcept {
		return !(lhs > rhs);
	}

	bool operator>=(const SectionData &lhs, const SectionData &rhs) noexcept {
		return !(lhs < rhs);
	}
}
