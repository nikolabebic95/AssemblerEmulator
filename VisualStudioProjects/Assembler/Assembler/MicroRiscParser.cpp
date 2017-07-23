#include "MicroRiscParser.h"
#include "InstructionLineParser.h"
#include "SectionStartLineParser.h"

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
		auto instructions = std::make_shared<InstructionLineParser>();
		auto sections = std::make_shared<SectionStartLineParser>();

		instructions->next(sections);

		head_ = instructions;
	}
}
