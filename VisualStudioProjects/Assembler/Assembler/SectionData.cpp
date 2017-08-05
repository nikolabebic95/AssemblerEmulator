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

	void SectionData::addData(uint8_t data, std::list<RelocationRecord> &relocations) {
		addData(data);
		for (auto &relocation : relocations) {
			relocation.offset(data_.size() - 1);
			relocation.dataType(BYTE);
		}

		relocation_records_.splice(relocation_records_.end(), move(relocations));
	}

	void SectionData::addData(uint16_t data, std::list<RelocationRecord> &relocations) {
		addData(static_cast<uint8_t>(data & 0x00FF));
		addData(static_cast<uint8_t>((data & 0xFF00) >> 8));
		for (auto &relocation : relocations) {
			relocation.offset(data_.size() - 2);
			relocation.dataType(WORD);
		}

		relocation_records_.splice(relocation_records_.end(), move(relocations));
	}

	void SectionData::addData(uint32_t data, std::list<RelocationRecord> &relocations) {
		addData(static_cast<uint8_t>(data & 0x000000FF));
		addData(static_cast<uint8_t>((data & 0x0000FF00) >> 8));
		addData(static_cast<uint8_t>((data & 0x00FF0000) >> 16));
		addData(static_cast<uint8_t>((data & 0xFF000000) >> 24));
		for (auto &relocation : relocations) {
			relocation.offset(data_.size() - 4);
			relocation.dataType(DOUBLE_WORD);
		}

		relocation_records_.splice(relocation_records_.end(), move(relocations));
	}

	void SectionData::org(uint32_t address) {
		org_address_ = address;
		org_valid_ = true;
	}

	void SectionData::addData(uint8_t data) {
		data_.push_back(data);
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
