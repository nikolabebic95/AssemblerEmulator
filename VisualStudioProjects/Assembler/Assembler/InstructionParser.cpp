#include "InstructionParser.h"
#include <regex>
#include "MessageException.h"

namespace bnss {

	std::vector<std::shared_ptr<Operand>> InstructionParser::parse(std::string str) const {
		static std::regex regex("[[:space:]]*(.*?)[[:space:]]*,(.*)");
		static std::regex last("[[:space:]]*(.*?)[[:space:]]*");

		std::vector<std::shared_ptr<Operand>> operands;

		for (size_t i = 0; i < operands_.size() - 1; i++) {
			if (!regex_match(str, regex)) {
				throw MessageException("Invalid instruction format: " + str);
			}

			auto operand_string = regex_replace(str, regex, "$1");
			str = regex_replace(str, regex, "$2");

			auto operand = operands_[i]->tryParse(operand_string);
			if (operand == nullptr) {
				throw MessageException("Invalid operand: " + operand_string);
			}

			operands.push_back(operand);
		}

		if (operands_.size() > 0) {
			if (!regex_match(str, last)) {
				throw MessageException("Invalid instruction format: " + str);
			}

			auto operand_string = regex_replace(str, last, "$1");
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
