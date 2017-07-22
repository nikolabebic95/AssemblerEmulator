#include "AluInstructionParser.h"
#include "RegisterDirectParser.h"

namespace bnss {

	AluInstructionParser::AluInstructionParser() noexcept {
		operands_.push_back(std::make_shared<RegisterDirectParser>());
		operands_.push_back(std::make_shared<RegisterDirectParser>());
		operands_.push_back(std::make_shared<RegisterDirectParser>());
	}
}
