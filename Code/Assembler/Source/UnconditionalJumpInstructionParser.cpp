#include "UnconditionalJumpInstructionParser.h"
#include "MemoryDirectParser.h"
#include "RegisterIndirectOffsetParser.h"
#include "RegisterIndirectParser.h"

namespace bnssassembler {

	UndonditionalJumpInstructionParser::UndonditionalJumpInstructionParser() noexcept {
		auto memdir = std::make_shared<MemoryDirectParser>();
		auto regindpom = std::make_shared<RegisterIndirectOffsetParser>();
		auto regind = std::make_shared<RegisterIndirectParser>();

		memdir->next(regindpom);
		regindpom->next(regind);

		operands_.push_back(memdir);
	}
}
