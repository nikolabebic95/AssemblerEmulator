#include "StackInstructionParser.h"
#include "RegisterDirectParser.h"

namespace bnssassembler {

	StackInstructionParser::StackInstructionParser() noexcept {
		operands_.push_back(std::make_shared<RegisterDirectParser>());
	}
}
