#include "RegisterIndirectParser.h"
#include <regex>
#include "RegisterParser.h"
#include "RegisterIndirect.h"

namespace bnss {

	std::shared_ptr<Operand> RegisterIndirectParser::parse(std::string str) const {
		static std::regex regex("[[:space:]]*\\[[[:space:]]*(.*)[[:space:]]*\\][[:space:]]*");
		if (!regex_match(str, regex)) {
			return nullptr;
		}

		auto reg_str = regex_replace(str, regex, "$1");

		auto reg = RegisterParser::parse(reg_str);
		return std::make_shared<RegisterIndirect>(reg);
	}
}
