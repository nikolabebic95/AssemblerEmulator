#include "InterruptInstructionParser.h"
#include "RegisterDirectParser.h"

namespace bnss {

	InterruptInstructionParser::InterruptInstructionParser() noexcept {
		operands_.push_back(std::make_shared<RegisterDirectParser>());
	}
}
