#include "ConditionalJumpInstructionParser.h"
#include "RegisterDirectParser.h"
#include "MemoryDirectParser.h"
#include "RegisterIndirectParser.h"
#include "RegisterIndirectOffsetParser.h"

namespace bnssassembler {

	ConditionalJumpInstructionParser::ConditionalJumpInstructionParser() noexcept {
		operands_.push_back(std::make_shared<RegisterDirectParser>());
		auto memdir = std::make_shared<MemoryDirectParser>();
		auto regindpom = std::make_shared<RegisterIndirectOffsetParser>();
		auto regind = std::make_shared<RegisterIndirectParser>();
		
		memdir->next(regindpom);
		regindpom->next(regind);
		
		operands_.push_back(memdir);
	}
}
