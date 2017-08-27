#ifndef _common_regexes_h_
#define _common_regexes_h_
#include <regex>

namespace bnssassembler {

	const std::string ZERO = "0";
	const std::string DECIMAL = "[1-9][0-9]*";
	const std::string HEX = "0x[0-9a-fA-F][0-9a-fA-F]*";
	const std::string BINARY = "0b[01][01]*";
	const std::string OCT = "0[0-7][0-7]*";
	const std::string CHARACTER = "'[[:print:]]'";

#ifdef _MSC_VER
	const std::string LITERAL = "(" + DECIMAL + "|" + HEX + "|" + BINARY + "|" + OCT + "|" + CHARACTER + "|" + ZERO + ")";
#else
	const std::string LITERAL = "(" + ZERO + "|" + DECIMAL + "|" + HEX + "|" + BINARY + "|" + OCT + "|" + CHARACTER + ")";
#endif

	const std::string OPERATOR = "[-+*/()]";
	const std::string SYMBOL = "(([a-zA-Z_][a-zA-Z_0-9]*)|\\$)";
	const std::string LABEL = SYMBOL;
	const std::string CONSTANT_TERM = "([[:space:]]*(" + LITERAL + "|" + OPERATOR + "|" + SYMBOL + ")[[:space:]]*)*";

	const std::string ORG_DIRECTIVE = "[Oo][Rr][Gg]";
	const std::string SYMBOL_DEFINITION = "[Dd][Ee][Ff]";
	const std::string DUPLICATE_DIRECTIVE = "[Dd][Uu][Pp]";
	const std::string GLOBAL_DIRECTIVE = "[.][Gg][Ll][Oo][Bb][Aa][Ll]";

	const std::string COMMA_TOKENIZER = "[[:space:]]*(.*?)[[:space:]]*,(.*)";
	const std::string LAST_COMMA_TOKEN = "[[:space:]]*(.*)[[:space:]]*";

	const std::regex ZERO_REGEX = std::regex(ZERO);
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

	const std::regex ORG_DIRECTIVE_REGEX = std::regex(ORG_DIRECTIVE);
	const std::regex SYMBOL_DEFINITION_REGEX = std::regex(SYMBOL_DEFINITION);
	const std::regex DUPLICATE_DIRECTIVE_REGEX = std::regex(DUPLICATE_DIRECTIVE);
	const std::regex GLOBAL_DIRECTIVE_REGEX = std::regex(GLOBAL_DIRECTIVE);

	const std::regex COMMA_TOKENIZER_REGEX = std::regex(COMMA_TOKENIZER);
	const std::regex LAST_COMMA_TOKEN_REGEX = std::regex(LAST_COMMA_TOKEN);
}

#endif
