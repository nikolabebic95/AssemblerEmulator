#include "SymbolDefinitionLineParser.h"
#include <regex>
#include "CommonRegexes.h"
#include "SymbolDefinitionToken.h"
#include "ExpressionBuilder.h"

namespace bnssassembler {

	std::shared_ptr<Token> SymbolDefinitionLineParser::parse(const std::string & line, size_t line_number, std::string initial_line) const {
		static std::regex regex("[[:space:]]*(" + SYMBOL + ")[[:space:]]*" + SYMBOL_DEFINITION + "(" + CONSTANT_TERM + ")");

		if (!regex_match(line, regex)) {
			return nullptr;
		}

		auto name = regex_replace(line, regex, "$1");
		auto expression_string = regex_replace(line, regex, "$2");
		auto expression = ExpressionBuilder::build(expression_string);

		return std::make_shared<SymbolDefinitionToken>(name, expression, line_number, initial_line);
	}
}
