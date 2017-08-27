#include "GlobalSymbolsLineParser.h"
#include <regex>
#include "CommonRegexes.h"
#include "StringHelper.h"
#include "GlobalSymbolToken.h"

namespace bnssassembler {

	std::shared_ptr<Token> GlobalSymbolsLineParser::parse(const std::string & line, size_t line_number, std::string initial_line) const {
		static std::regex regex("[[:space:]]*" + GLOBAL_DIRECTIVE + "(.*)[[:space:]]*");
		static std::regex symbol_regex("[[:space:]]*(" + SYMBOL + ")[[:space:]]*");

		if (!regex_match(line, regex)) {
			return nullptr;
		}

		auto symbols_string = regex_replace(line, regex, "$1");
		auto symbols = StringHelper::split(symbols_string, ",");

		std::vector<std::string> ret;
		for (auto &symbol : symbols) {
			if (!regex_match(symbol, symbol_regex)) {
				throw MessageException(symbol + " is not a valid symbol");
			}

			ret.push_back(regex_replace(symbol, symbol_regex, "$1"));
		}

		return std::make_shared<GlobalSymbolsToken>(ret, line_number, initial_line);
	}
}
