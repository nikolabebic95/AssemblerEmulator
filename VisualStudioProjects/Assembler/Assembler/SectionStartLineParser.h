#ifndef _section_start_line_parser_h_
#define _section_start_line_parser_h_
#include "LineParser.h"

namespace bnss {
	
	/**
	 * \brief Class used for parsing section start definitions
	 */
	class SectionStartLineParser : public LineParser {
	protected:
		std::shared_ptr<Token> parse(const std::string &line, size_t line_number, std::string initial_line) const override;
	};
}

#endif
