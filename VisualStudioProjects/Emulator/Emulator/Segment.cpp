#include "Segment.h"
#include "MessageException.h"
#include "StringHelper.h"
#include "InstructionBitFieldUnion.h"

namespace bnssemulator {

	Segment::Segment(uint32_t address, size_t length, SectionType type, vector<uint8_t> &&data) : vector(move(data)), address_(address), length_(length), type_(type) {
		if (size() == 0) {
			resize(length);
		}
	}

	InstructionBitField Segment::getInstruction(uint32_t address) const {
		if (type_ != TEXT) {
			throw MessageException("No execute permission at address " + StringHelper::toHexString(address));
		}
		
		if (address < address_ || address + 4 > address_ + length_) {
			throw MessageException("Address " + StringHelper::toHexString(address) + " is out of range");
		}

		auto offset = address - address_;
		InstructionBitFieldUnion ret;
		ret.data = 0;

		ret.data |= (*this)[offset];
		ret.data |= (*this)[offset + 1] << 8;
		ret.data |= (*this)[offset + 2] << 16;
		ret.data |= (*this)[offset + 3] << 24;

		return ret.bit_field;
	}

	uint8_t Segment::readData(uint32_t address) const {
		if (type_ == TEXT) {
			throw MessageException("No read permission at address " + StringHelper::toHexString(address));
		}

		if (address < address_ || address > address_ + length_) {
			throw MessageException("Address " + StringHelper::toHexString(address) + " is out of range");
		}

		auto offset = address - address_;
		return (*this)[offset];
	}

	void Segment::writeData(uint32_t address, uint8_t data) {
		if (type_ != DATA && type_ != BSS) {
			throw MessageException("No read permission at address " + StringHelper::toHexString(address));
		}

		if (address < address_ || address > address_ + length_) {
			throw MessageException("Address " + StringHelper::toHexString(address) + " is out of range");
		}

		auto offset = address - address_;
		(*this)[offset] = data;
	}

	void Segment::relocate(uint32_t address, uint32_t relocation) {
		if (address < address_ || address + 4 > address_ + length_) {
			throw MessageException("Address " + StringHelper::toHexString(address) + " is out of range");
		}

		auto offset = address - address_;

		uint32_t data = 0;

		data |= (*this)[offset];
		data |= (*this)[offset + 1] << 8;
		data |= (*this)[offset + 2] << 16;
		data |= (*this)[offset + 3] << 24;

		data += relocation;

		(*this)[offset] = static_cast<uint8_t>(data & 0x000000ff);
		(*this)[offset + 1] = static_cast<uint8_t>((data & 0x0000ff00) >> 8);
		(*this)[offset + 2] = static_cast<uint8_t>((data & 0x00ff0000) >> 16);
		(*this)[offset + 3] = static_cast<uint8_t>((data & 0xff000000) >> 24);
	}
}
