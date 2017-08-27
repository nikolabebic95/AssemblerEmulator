#include "OrgDirectiveLineParser.h"
#include <regex>
#include "CommonRegexes.h"
#include "ExpressionBuilder.h"
#include "OrgDirectiveToken.h"

namespace bnssassembler {

	std::shared_ptr<Token> OrgDirectiveLineParser::parse(const std::string & line, size_t line_number, std::string initial_line) const {
		static std::regex regex("[[:space:]]*" + ORG_DIRECTIVE + "(" + CONSTANT_TERM + ")");

		if (!regex_match(line, regex)) {
			return nullptr;
		}

		auto expression_string = regex_replace(line, regex, "$1");
		auto expression = ExpressionBuilder::build(expression_string);
		return std::make_shared<OrgDirectiveToken>(expression, line_number, initial_line);
	}
}
