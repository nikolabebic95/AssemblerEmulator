#include "RegisterIndirectOffsetParser.h"
#include <regex>
#include "RegisterParser.h"
#include "ExpressionBuilder.h"
#include "RegisterIndirectOffset.h"

namespace bnss {

	std::shared_ptr<Operand> RegisterIndirectOffsetParser::parse(std::string str) const {
		static std::regex regex("[[:space:]]*\\[[[:space:]]*([A-Za-z0-9]*)[[:space:]]*(.*)\\][[:space:]]*");
		if (!regex_match(str, regex)) {
			return nullptr;
		}
		
		auto reg_str = regex_replace(str, regex, "$1");
		auto off_str = "0" + regex_replace(str, regex, "$2");

		// This would be register indirect without offset
		if (off_str == "0") {
			return nullptr;
		}
			
		auto reg = RegisterParser::parse(reg_str);
		auto off = ExpressionBuilder::build(off_str);
		return std::make_shared<RegisterIndirectOffset>(reg, off);
	}
}
