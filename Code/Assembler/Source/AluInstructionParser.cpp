#include "AluInstructionParser.h"
#include "RegisterDirectParser.h"

namespace bnssassembler {

	AluInstructionParser::AluInstructionParser() noexcept {
		operands_.push_back(std::make_shared<RegisterDirectParser>());
		operands_.push_back(std::make_shared<RegisterDirectParser>());
		operands_.push_back(std::make_shared<RegisterDirectParser>());
	}
}
