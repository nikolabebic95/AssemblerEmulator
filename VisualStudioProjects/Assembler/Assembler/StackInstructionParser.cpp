#include "StackInstructionParser.h"
#include "RegisterDirectParser.h"

namespace bnss {

	StackInstructionParser::StackInstructionParser() noexcept {
		operands_.push_back(std::make_shared<RegisterDirectParser>());
	}
}
