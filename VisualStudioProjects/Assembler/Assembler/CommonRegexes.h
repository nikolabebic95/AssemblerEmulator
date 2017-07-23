#ifndef _common_regexes_h_
#define _common_regexes_h_
#include <regex>

namespace bnss {

	const std::string DECIMAL = "[1-9][0-9]*";
	const std::string HEX = "0x[0-9a-fA-F][0-9a-fA-F]*";
	const std::string BINARY = "0b[01][01]*";
	const std::string OCT = "0[0-7]*";
	const std::string CHARACTER = "'[[:print:]]'";

	const std::string LITERAL = "(" + DECIMAL + "|" + HEX + "|" + BINARY + "|" + OCT + "|" + CHARACTER + ")";
	const std::string OPERATOR = "[-+*/()]";
	const std::string SYMBOL = "[a-zA-Z_$][a-zA-Z_$0-9]*";
	const std::string LABEL = SYMBOL;
	const std::string CONSTANT_TERM = "([[:space:]]*(" + LITERAL + "|" + OPERATOR + "|" + SYMBOL + ")[[:space:]]*)*";

	const std::regex DECIMAL_REGEX = std::regex(DECIMAL);
	const std::regex HEX_REGEX = std::regex(HEX);
	const std::regex BINARY_REGEX = std::regex(BINARY);
	const std::regex OCT_REGEX = std::regex(OCT);
	const std::regex CHARACTER_REGEX = std::regex(CHARACTER);

	const std::regex LITERAL_REGEX = std::regex(LITERAL);
	const std::regex OPERATOR_REGEX = std::regex(OPERATOR);
	const std::regex SYMBOL_REGEX = std::regex(SYMBOL);
	const std::regex LABEL_REGEX = std::regex(LABEL);
	const std::regex CONSTANT_TERM_REGEX = std::regex(CONSTANT_TERM);
}

#endif
