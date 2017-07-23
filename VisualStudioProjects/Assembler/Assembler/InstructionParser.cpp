#include "InstructionParser.h"
#include <regex>
#include "MessageException.h"
#include "CommonRegexes.h"

namespace bnss {

	std::vector<std::shared_ptr<Operand>> InstructionParser::parse(std::string str) const {
		std::vector<std::shared_ptr<Operand>> operands;

		for (size_t i = 0; i < operands_.size() - 1; i++) {
			if (!regex_match(str, COMMA_TOKENIZER_REGEX)) {
				throw MessageException("Invalid instruction format: " + str);
			}

			auto operand_string = regex_replace(str, COMMA_TOKENIZER_REGEX, "$1");
			str = regex_replace(str, COMMA_TOKENIZER_REGEX, "$2");

			auto operand = operands_[i]->tryParse(operand_string);
			if (operand == nullptr) {
				throw MessageException("Invalid operand: " + operand_string);
			}

			operands.push_back(operand);
		}

		if (operands_.size() > 0) {
			if (!regex_match(str, LAST_COMMA_TOKEN_REGEX)) {
				throw MessageException("Invalid instruction format: " + str);
			}

			auto operand_string = regex_replace(str, LAST_COMMA_TOKEN_REGEX, "$1");
			auto operand = operands_[operands_.size() - 1]->tryParse(operand_string);
			if (operand == nullptr) {
				throw MessageException("Invalid operand: " + operand_string);
			}

			operands.push_back(operand);
		}

		return operands;
	}

	InstructionParser::~InstructionParser() {}
}
