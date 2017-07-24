#include "RegisterIndirectOffsetParser.h"
#include <regex>
#include "RegisterParser.h"
#include "ExpressionBuilder.h"
#include "RegisterIndirectOffset.h"
#include "CommonRegexes.h"

namespace bnss {

	/**
	 * \brief Parses the input as a PC relative address
	 * \param str String representation of an operand
	 * \return Pointer to the parsed operand or nullptr if the input is not a PC relative address
	 * \throw Throws if the string could not be parsed
	 */
	std::shared_ptr<Operand> parsePcrel(std::string str) {
		static std::regex regex("[[:space:]]*\\$(" + CONSTANT_TERM + ")");

		if (!regex_match(str, regex)) {
			return nullptr;
		}

		auto address_string = regex_replace(str, regex, "$1");
		auto address = ExpressionBuilder::build(address_string);
		return std::make_shared<RegisterIndirectOffset>(PC, address, true);
	}

	std::shared_ptr<Operand> RegisterIndirectOffsetParser::parse(std::string str) const {
		static std::regex regex("[[:space:]]*\\[[[:space:]]*([A-Za-z0-9]*)[[:space:]]*(.*)\\][[:space:]]*");
		if (!regex_match(str, regex)) {
			return parsePcrel(str);
		}
		
		auto reg_str = regex_replace(str, regex, "$1");
		auto off_str = "0" + regex_replace(str, regex, "$2");

		// This would be register indirect without offset
		if (off_str == "0") {
			return nullptr;
		}
			
		auto reg = RegisterParser::parse(reg_str);
		auto off = ExpressionBuilder::build(off_str);
		return std::make_shared<RegisterIndirectOffset>(reg, off, false);
	}
}
