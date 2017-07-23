#include "MicroRiscParser.h"
#include "InstructionLineParser.h"
#include "SectionStartLineParser.h"
#include "OrgDirectiveLineParser.h"
#include "SymbolDefinitionLineParser.h"
#include "DataDefinitionLineParser.h"

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
		auto data = std::make_shared<DataDefinitionLineParser>();
		auto sections = std::make_shared<SectionStartLineParser>();
		auto org = std::make_shared<OrgDirectiveLineParser>();
		auto symbol = std::make_shared<SymbolDefinitionLineParser>();

		instructions->next(data);
		data->next(sections);
		sections->next(org);
		org->next(symbol);

		head_ = instructions;
	}
}
