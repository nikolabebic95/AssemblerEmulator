#include "SectionData.h"
#include "StringHelper.h"
#include <iostream>
#include "PrintHelpers.h"

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

	size_t SectionData::size() const noexcept {
		return data_.size();
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

	static std::string name(SectionType type, bool indexed, size_t index) {
		std::string ret(" .");
		switch (type) {
		case TEXT: 
			ret += "text";
			break;
		case DATA: 
			ret += "data";
			break;
		case RODATA: 
			ret += "rodata";
			break;
		case BSS: 
			ret += "bss";
			break;
		default: 
			break;
		}

		if (indexed) {
			ret += "." + std::to_string(index);
		}

		return ret;
	}

	static void writeDescription(SectionType type, bool indexed, size_t index, bool org_valid, uint32_t org_address) {
		std::cout << UPPER_LEFT << multiple(HORIZONTAL, 81) << UPPER_RIGHT << std::endl;
		auto description = name(type, indexed, index) + (org_valid ? " ORG: " + StringHelper::toHexString(org_address) : "");
		std::cout << VERTICAL << std::setw(81) << std::left << description << VERTICAL << std::endl;
		std::cout << T_RIGHT << multiple(HORIZONTAL, 81) << T_LEFT << std::endl;
	}

	std::ostream & operator<<(std::ostream &os, const SectionData &data) {
		os << data.type_ << std::endl;
		os << data.indexed_ << std::endl;
		if (data.indexed_) {
			os << data.index_ << std::endl;
		}

		os << data.org_valid_ << std::endl;
		if (data.org_valid_) {
			os << data.org_address_ << std::endl;
		}

		os << data.data_.size() << std::endl;
		for (auto &entry : data.data_) {
			os << StringHelper::numberFormat(entry) << std::endl;
		}

		writeDescription(data.type_, data.indexed_, data.index_, data.org_valid_, data.org_address_);

		std::cout << VERTICAL << " ";

		size_t i;
		for (i = 0; i < data.data_.size(); i++) {
			auto entry = data.data_[i];
			if (i % 16 == 0 && i != 0) {
				std::cout << VERTICAL << std::endl << VERTICAL << " ";
			}

			std::cout << StringHelper::toHexString(entry) << " ";
		}

		for (; i % 16 != 0; i++) {
			std::cout << "     ";
		}

		std::cout << VERTICAL << std::endl;

		std::cout << T_RIGHT << multiple(HORIZONTAL, 81) << T_LEFT << std::endl;
		std::cout << VERTICAL << std::setw(81) << std::left << " Relocation table:" << VERTICAL << std::endl;
		std::cout << T_RIGHT << multiple(HORIZONTAL, 8) << T_DOWN << multiple(HORIZONTAL, 10) << T_DOWN << multiple(HORIZONTAL, 9) << T_DOWN << multiple(HORIZONTAL, 51) << T_LEFT << std::endl;
		
		std::cout << VERTICAL << " Offset " << VERTICAL << " Absolute " << VERTICAL << " Section " << VERTICAL << "                      Symbol                       " << VERTICAL << std::endl;
		std::cout << T_RIGHT << multiple(HORIZONTAL, 8) << ALL_FOUR << multiple(HORIZONTAL, 10) << ALL_FOUR << multiple(HORIZONTAL, 9) << ALL_FOUR << multiple(HORIZONTAL, 51) << T_LEFT << std::endl;

		for (auto &record : data.relocation_records_) {
			os << record << std::endl;
		}

		std::cout << LOWER_LEFT << multiple(HORIZONTAL, 8) << T_UP << multiple(HORIZONTAL, 10) << T_UP << multiple(HORIZONTAL, 9) << T_UP << multiple(HORIZONTAL, 51) << LOWER_RIGHT << std::endl;

		return os;
	}
}
