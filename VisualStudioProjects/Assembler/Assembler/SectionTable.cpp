#include "SectionTable.h"
#include "MessageException.h"
#include "SectionTypeParser.h"

namespace bnss {

	SectionTable & SectionTable::operator+=(const SectionData & data) {
		if (set_.count(data) > 0) {
			auto section_string = "." + SectionTypeParser::toString(data.type()) + (data.indexed() ? "." + data.index() : "");
			throw MessageException("Section " + section_string + " already exists");
		}

		set_.insert(data);
		push_back(data);
		return *this;
	}

	void SectionTable::nextSection() noexcept {
		current_index_++;
	}

	SectionType SectionTable::currentSectionType() const noexcept {
		return (*this)[current_index_].type();
	}

	void SectionTable::addData(uint8_t data, std::list<RelocationRecord> &relocations) {
		(*this)[current_index_].addData(data, relocations);
	}

	void SectionTable::addData(uint16_t data, std::list<RelocationRecord> &relocations) {
		(*this)[current_index_].addData(data, relocations);
	}

	void SectionTable::addData(uint32_t data, std::list<RelocationRecord> &relocations) {
		(*this)[current_index_].addData(data, relocations);
	}

	SectionData & SectionTable::current() noexcept {
		return (*this)[current_index_];
	}

	const SectionData & SectionTable::current() const noexcept {
		return const_cast<SectionTable &>(*this).current();
	}
}
