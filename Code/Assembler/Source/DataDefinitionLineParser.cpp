#include "DataDefinitionLineParser.h"
#include <regex>
#include "CommonRegexes.h"
#include "Data.h"
#include "InvalidDataDefinitionException.h"
#include "DataDefinitionToken.h"
#include "InvalidDataTypeException.h"
#include "DataTypeParser.h"
#include "ExpressionBuilder.h"

namespace bnssassembler {

	/** 
	 * \brief Parses the data from the string
	 * \param str String that will be parsed
	 * \return Parsed data
	 * \throw Throws if the data could not be parsed
	 */
	Data parseData(std::string str) {
		static std::regex splitter("(.*)" + DUPLICATE_DIRECTIVE + "(.*)");
		static std::regex left_regex("[[:space:]]*([Dd][BbWwDd])(" + CONSTANT_TERM + ")");
		static std::regex uninitialized_value("[[:space:]]*\\?[[:space:]]*");

		auto left = str;
		std::string right;

		if (regex_match(str, splitter)) {
			left = regex_replace(str, splitter, "$1");
			right = regex_replace(str, splitter, "$2");
		}

		if (!regex_match(left, left_regex)) {
			throw InvalidDataDefinitionException(str);
		}

		auto data_type_string = regex_replace(left, left_regex, "$1");
		auto left_expression_string = regex_replace(left, left_regex, "$2");
		
		auto data_type = DataTypeParser::parse(data_type_string);
		auto left_expression = ExpressionBuilder::build(left_expression_string);

		if (right.empty()) {
			return Data(data_type, left_expression, ExpressionBuilder::build("1"));
		}

		if (regex_match(right, uninitialized_value)) {
			return Data(data_type, left_expression);
		}

		auto right_expression = ExpressionBuilder::build(right);
		return Data(data_type, right_expression, left_expression);
	}

	std::shared_ptr<Token> DataDefinitionLineParser::parse(const std::string & line, size_t line_number, std::string initial_line) const {
		auto parsed_line = line;
		std::vector<Data> data_vector;
		
		static std::regex comma("(.*)','(.*)");

		while (true) {
			if (!regex_match(parsed_line, COMMA_TOKENIZER_REGEX) || regex_match(parsed_line, comma)) {
				break;
			}

			auto comma_token = regex_replace(parsed_line, COMMA_TOKENIZER_REGEX, "$1");
			parsed_line = regex_replace(parsed_line, COMMA_TOKENIZER_REGEX, "$2");

			try {
				data_vector.push_back(parseData(comma_token));
			}
			catch (InvalidDataDefinitionException &) {
				return nullptr;
			}
			catch (InvalidDataTypeException &) {
				return nullptr;
			}
		}

		if (!regex_match(parsed_line, LAST_COMMA_TOKEN_REGEX)) {
			return nullptr;
		}

		auto comma_token = regex_replace(parsed_line, LAST_COMMA_TOKEN_REGEX, "$1");
		try {
			data_vector.push_back(parseData(comma_token));
		}
		catch (InvalidDataDefinitionException &) {
			return nullptr;
		}
		catch (InvalidDataTypeException &) {
			return nullptr;
		}

		return std::make_shared<DataDefinitionToken>(data_vector, line_number, initial_line);
	}
}
