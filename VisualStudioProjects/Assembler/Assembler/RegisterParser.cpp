#include "RegisterParser.h"
#include "MessageException.h"
#include <algorithm>
#include <regex>

namespace bnss {

	Register RegisterParser::parse(std::string str) {
		static std::regex regex("[[:space:]]*([a-z0-9]*)[[:space:]]*");
		transform(str.begin(), str.end(), str.begin(), tolower);

		if (!regex_match(str, regex)) {
			throw MessageException("Invalid register: " + str);
		}

		str = regex_replace(str, regex, "$1");

		if (staticData().map.count(str) == 0) {
			throw MessageException("Invalid register: " + str);
		}

		return staticData().map[str];
	}

	RegisterParser::RegisterParserStaticData &RegisterParser::staticData() noexcept {
		static RegisterParserStaticData static_data;
		return static_data;
	}

	RegisterParser::RegisterParserStaticData::RegisterParserStaticData() noexcept {
		for (auto i = 0; i < NUM_OF_REGISTERS; i++) {
			map["r" + std::to_string(i)] = static_cast<Register>(i);
		}

		map["pc"] = PC;
		map["sp"] = SP;
	}
}
