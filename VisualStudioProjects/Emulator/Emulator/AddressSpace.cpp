#include "AddressSpace.h"
#include "StringHelper.h"
#include "StlHelper.h"
#include <list>
#include <set>
#include "SymbolData.h"
#include <unordered_map>
#include <iostream>

namespace bnssemulator {

	static void removeEmpty(std::vector<SectionData> &section_table) {
		size_t j = 0;
		for (size_t i = 0; i < section_table.size(); i++) {
			if (section_table[i].size() != 0) {
				section_table[j++] = section_table[i];
			}
		}

		section_table.resize(j);
	}

	static bool checkOverlaps(const std::vector<SectionData> &section_table) {
		std::vector<std::pair<uint32_t, uint32_t>> check;
		for (auto &section : section_table) {
			if (section.hasAddress()) {
				check.push_back(std::make_pair(section.address(), section.address() + section.size() - 1));
			}
		}

		sort(check.begin(), check.end(), compare_pair_first<uint32_t, uint32_t>());

		for (size_t i = 1; i < check.size(); i++) {
			if (check[i - 1].second >= check[i].first) {
				return true;
			}
		}

		return false;
	}

	static std::list<std::pair<uint32_t, uint32_t>> getAvailable(const std::vector<SectionData>& section_table) {
		std::set<std::pair<uint32_t, uint32_t>, compare_pair_first<uint32_t, uint32_t>> set{{0, 0xffffffff}};
		for (auto &section : section_table) {
			if (section.hasAddress()) {
				auto section_pair = std::make_pair(section.address(), section.address() + section.size() - 1);
				auto upper = set.upper_bound(section_pair);
				--upper;

				auto left = std::make_pair(upper->first, section_pair.first - 1);
				auto right = std::make_pair(section_pair.second + 1, upper->second);
				set.erase(upper);

				if (left.first != left.second + 1) {
					set.insert(left);
				}

				if (right.first != right.second + 1) {
					set.insert(right);
				}
			}
		}

		std::list<std::pair<uint32_t, uint32_t>> ret;
		for (auto &entry : set) {
			ret.push_back(entry);
		}

		return ret;
	}

	// First fit algorithm:
	//   Loop through all the sections and for each section do the following:
	//     Find the first available spot
	//     Put the section there
	//     Update the available list
	static void generateAddresses(std::vector<SectionData> &section_table, std::list<std::pair<uint32_t, uint32_t>> &available) {
		for (auto &section : section_table) {
			if (!section.hasAddress()) {
				auto found = false;
				for (auto iterator = available.begin(); iterator != available.end(); ++iterator) {
					if (iterator->second - iterator->first >= section.size()) {
						found = true;
						section.address(iterator->first);
						iterator->first += section.size();
						if (iterator->first == iterator->second) {
							available.erase(iterator);
						}

						break;
					}
				}

				if (!found) {
					throw MessageException("There is not enough space for all the sections");
				}
			}
		}
	}

	AddressSpace::AddressSpace(std::vector<SectionData>&& section_table, const std::unordered_map<std::string, SymbolData> symbol_table) {
		removeEmpty(section_table);

		if (checkOverlaps(section_table)) {
			throw MessageException("Sections are overlapping");
		}

		auto available = getAvailable(section_table);
		generateAddresses(section_table, available);
		
		for (auto &section : section_table) {
			insert(make_pair(section.address(), Segment(section.address(), section.size(), section.type(), move(section.data()))));
		}

		for (auto &section : section_table) {
			for (auto &relocation_entry : section.relocations()) {
				uint32_t relocation;

				if (relocation_entry.section()) {
					relocation = section_table.at(relocation_entry.sectionIndex()).address();
				}
				else {
					auto &symbol = symbol_table.at(relocation_entry.symbolName());
					relocation = section_table.at(symbol.sectionIndex()).address() + symbol.offset();
				}

				if (!relocation_entry.absolute()) {
					relocation -= section.address() + relocation_entry.offset();
				}

				at(section.address()).relocate(section.address() + relocation_entry.offset(), relocation);
			}
		}
	}

	InstructionBitField AddressSpace::getInstruction(uint32_t address) const {
		return segment(address).getInstruction(address);
	}

	int32_t AddressSpace::getSecondWordOfInstruction(uint32_t address) const {
		return segment(address).getSecondWordOfInstruction(address);
	}

	uint8_t AddressSpace::get8bitData(uint32_t address) const {
		if (address == stdin_address_) {
			stdin_read_ = true;
		}

		return segment(address).readData(address);
	}

	uint16_t AddressSpace::get16bitData(uint32_t address) const {
		return get8bitData(address) | (static_cast<uint16_t>(get8bitData(address + 1)) << 8);
	}

	uint32_t AddressSpace::get32bitData(uint32_t address) const {
		return get16bitData(address) | (static_cast<uint32_t>(get16bitData(address + 2)) << 16);
	}

	void AddressSpace::set8bitData(uint32_t address, uint8_t data) {
		segment(address).writeData(address, data);
		if (address == stdout_address_) {
			std::cout << data;
		}
		else if (address == stdin_address_) {
			stdin_read_ = false;
		}
	}

	void AddressSpace::set16bitData(uint32_t address, uint16_t data) {
		set8bitData(address, static_cast<uint8_t>(data & 0x00ff));
		set8bitData(address + 1, static_cast<uint8_t>((data & 0xff00) >> 8));
	}

	void AddressSpace::set32bitData(uint32_t address, uint32_t data) {
		set16bitData(address, static_cast<uint16_t>(data & 0x0000ffff));
		set16bitData(address + 2, static_cast<uint16_t>((data & 0xffff0000) >> 16));
	}

	uint32_t AddressSpace::initialStackPointer() const {
		try {
			return get32bitData(0);
		}
		catch (...) {
			throw MessageException("Initial stack pointer value is not defined");
		}
	}

	size_t AddressSpace::errorInterrupt() const noexcept {
		return error_interrupt_;
	}

	size_t AddressSpace::timerInterrupt() const noexcept {
		return timer_interrupt_;
	}

	size_t AddressSpace::keyboardInterrupt() const noexcept {
		return keyboard_interrupt_;
	}

	uint32_t AddressSpace::getInterrupt(uint32_t entry) const noexcept {
		try {
			return get32bitData(entry * 4);
		}
		catch (...) {
			return 0;
		}
	}

	bool AddressSpace::stdinRead() const noexcept {
		return stdin_read_;
	}

	void AddressSpace::writeToStdin(char character) noexcept {
		set8bitData(stdin_address_, character);
	}

	Segment & AddressSpace::segment(uint32_t address) {
		auto upper = upper_bound(address);
		if (upper == begin()) {
			throw std::runtime_error("The address " + StringHelper::toHexString(address) + " is out of emulated scope");
		}

		--upper;
		return upper->second;
	}

	const Segment & AddressSpace::segment(uint32_t address) const {
		return const_cast<AddressSpace &>(*this).segment(address);
	}
}
