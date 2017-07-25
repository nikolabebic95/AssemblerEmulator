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
}
