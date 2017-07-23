#ifndef _symbol_definition_line_parser_h_
#define _symbol_definition_line_parser_h_
#include "LineParser.h"

namespace bnss {
	
	class SymbolDefinitionLineParser : public LineParser {
	protected:
		std::shared_ptr<Token> parse(const std::string &line, size_t line_number, std::string initial_line) const override;
	};
}

#endif
