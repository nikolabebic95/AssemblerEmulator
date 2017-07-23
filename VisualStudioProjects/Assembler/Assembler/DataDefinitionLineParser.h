#ifndef _data_definition_line_parser_h_
#define _data_definition_line_parser_h_
#include "LineParser.h"

namespace bnss {
	
	class DataDefinitionLineParser : public LineParser {
	protected:
		std::shared_ptr<Token> parse(const std::string &line, size_t line_number, std::string initial_line) const override;
	};
}

#endif
