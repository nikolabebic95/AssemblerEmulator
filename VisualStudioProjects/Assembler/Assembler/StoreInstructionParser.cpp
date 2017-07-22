#include "StoreInstructionParser.h"
#include "MemoryDirectParser.h"
#include "RegisterIndirectOffsetParser.h"
#include "RegisterIndirectParser.h"
#include "RegisterDirectParser.h"

namespace bnss {

	StoreInstructionParser::StoreInstructionParser() noexcept {
		operands_.push_back(std::make_shared<RegisterDirectParser>());

		auto memdir = std::make_shared<MemoryDirectParser>();
		auto regindpom = std::make_shared<RegisterIndirectOffsetParser>();
		auto regind = std::make_shared<RegisterIndirectParser>();
		auto regdir = std::make_shared<RegisterDirectParser>();

		memdir->next(regindpom);
		regindpom->next(regind);
		regind->next(regdir);

		operands_.push_back(memdir);

	}
}
