#include "SectionTypeParser.h"
#include "MessageException.h"
#include <algorithm>

namespace bnss {
	SectionType SectionTypeParser::parse(std::string type) {
		transform(type.begin(), type.end(), type.begin(), tolower);

		if (staticData().map.count(type) == 0) {
			throw MessageException(type + " is not a valid section");
		}

		return staticData().map[type];
	}

	SectionTypeParser::SectionTypeParserData & SectionTypeParser::staticData() noexcept {
		static SectionTypeParserData static_data;
		return static_data;
	}

	SectionTypeParser::SectionTypeParserData::SectionTypeParserData() {
		map["text"] = TEXT;
		map["data"] = DATA;
		map["rodata"] = RODATA;
		map["bss"] = BSS;
	}
}
