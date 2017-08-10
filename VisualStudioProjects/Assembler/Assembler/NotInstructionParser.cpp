#include "NotInstructionParser.h"
#include "RegisterDirectParser.h"

namespace bnssassembler {

	NotInstructionParser::NotInstructionParser() noexcept {
		operands_.push_back(std::make_shared<RegisterDirectParser>());
		operands_.push_back(std::make_shared<RegisterDirectParser>());
	}
}
