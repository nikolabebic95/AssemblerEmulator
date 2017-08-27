#include "ImmediateParser.h"
#include <regex>
#include "CommonRegexes.h"
#include "ExpressionBuilder.h"
#include "Immediate.h"

namespace bnssassembler {

	std::shared_ptr<Operand> ImmediateParser::parse(std::string str) const {
		static std::regex regex("#(" + CONSTANT_TERM + ")");

		if (!regex_match(str, regex)) {
			return nullptr;
		}
		
		auto constant_term_string = regex_replace(str, regex, "$1");
		auto expression = ExpressionBuilder::build(constant_term_string);
		return std::make_shared<Immediate>(expression);
	}
}
