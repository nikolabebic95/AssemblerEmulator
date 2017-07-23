#ifndef _instruction_line_parser_h_
#define _instruction_line_parser_h_
#include "LineParser.h"
#include <unordered_map>
#include "InstructionCode.h"

namespace bnss {
	class InstructionParser;

	class InstructionLineParser : public LineParser {
	public:
		InstructionLineParser() noexcept;
	protected:
		std::shared_ptr<Token> parse(const std::string &line, size_t line_number, std::string initial_line) const override;
	private:
		std::unordered_map<InstructionCode, std::shared_ptr<InstructionParser>> instructions_;
	};
}

#endif
