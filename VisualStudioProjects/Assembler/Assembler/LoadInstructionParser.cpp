#include "LoadInstructionParser.h"
#include "RegisterDirectParser.h"
#include "MemoryDirectParser.h"
#include "RegisterIndirectOffsetParser.h"
#include "RegisterIndirectParser.h"
#include "ImmediateParser.h"

namespace bnss {

	LoadInstructionParser::LoadInstructionParser() noexcept {
		operands_.push_back(std::make_shared<RegisterDirectParser>());

		auto immed = std::make_shared<ImmediateParser>();
		auto regdir = std::make_shared<RegisterDirectParser>();
		auto memdir = std::make_shared<MemoryDirectParser>();
		auto regindpom = std::make_shared<RegisterIndirectOffsetParser>();
		auto regind = std::make_shared<RegisterIndirectParser>();

		immed->next(regdir);
		regdir->next(memdir);
		memdir->next(regindpom);
		regindpom->next(regind);

		operands_.push_back(immed);
	}
}
