#include "MemoryDirectParser.h"
#include <regex>
#include "CommonRegexes.h"
#include "ExpressionBuilder.h"
#include "MemoryDirect.h"

namespace bnss {

	std::shared_ptr<Operand> MemoryDirectParser::parse(std::string str) const {
		if (!regex_match(str, CONSTANT_TERM_REGEX)) {
			return nullptr;
		}

		auto expression = ExpressionBuilder::build(str);
		return std::make_shared<MemoryDirect>(expression);
	}
}
