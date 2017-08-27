#ifndef _global_symbols_line_parser_h_
#define _global_symbols_line_parser_h_
#include "LineParser.h"

namespace bnssassembler {
	
	/**
	 * \brief Class used for parsing information about global symbols
	 */
	class GlobalSymbolsLineParser : public LineParser {
	protected:
		std::shared_ptr<Token> parse(const std::string &line, size_t line_number, std::string initial_line) const override;
	};
}

#endif
