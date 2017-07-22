#include "MicroRiscParser.h"
#include "InstructionLineParser.h"

namespace bnss {

	MicroRiscParser &MicroRiscParser::instance() noexcept {
		static MicroRiscParser instance;
		return instance;
	}

	std::vector<std::string> MicroRiscParser::oneLineCommentDelimiters() const noexcept {
		return { ";", "//" };
	}

	std::vector<std::string> MicroRiscParser::labelDelimiters() const noexcept {
		return { ":" };
	}

	std::shared_ptr<LineParser> MicroRiscParser::chain() const noexcept {
		return head_;
	}

	MicroRiscParser::MicroRiscParser() {
		head_ = std::make_shared<InstructionLineParser>();
	}

}
