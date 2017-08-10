#include "MicroRiscParser.h"
#include "InstructionLineParser.h"
#include "SectionStartLineParser.h"
#include "OrgDirectiveLineParser.h"
#include "SymbolDefinitionLineParser.h"
#include "DataDefinitionLineParser.h"
#include "GlobalSymbolsLineParser.h"
#include <regex>

namespace bnssassembler {

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

	bool MicroRiscParser::isEnd(std::string line) const noexcept {
		static std::regex regex("[[:space:]]*[.][Ee][Nn][Dd][[:space:]]*");
		return regex_match(line, regex);
	}

	std::shared_ptr<LineParser> MicroRiscParser::chain() const noexcept {
		return head_;
	}

	MicroRiscParser::MicroRiscParser() {
		auto instructions = std::make_shared<InstructionLineParser>();
		auto data = std::make_shared<DataDefinitionLineParser>();
		auto sections = std::make_shared<SectionStartLineParser>();
		auto global = std::make_shared<GlobalSymbolsLineParser>();
		auto org = std::make_shared<OrgDirectiveLineParser>();
		auto symbol = std::make_shared<SymbolDefinitionLineParser>();

		instructions->next(data);
		data->next(sections);
		sections->next(global);
		global->next(org);
		org->next(symbol);

		head_ = instructions;
	}
}
