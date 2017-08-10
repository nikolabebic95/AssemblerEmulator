#ifndef _org_directive_line_parser_h_
#define _org_directive_line_parser_h_
#include "LineParser.h"

namespace bnssassembler {
	
	/**
	 * \brief Class representing a line parser for the origin directive
	 */
	class OrgDirectiveLineParser : public LineParser {
	protected:
		std::shared_ptr<Token> parse(const std::string &line, size_t line_number, std::string initial_line) const override;
	};
}

#endif
