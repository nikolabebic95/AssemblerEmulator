#include "ParserException.h"

namespace bnss {
	std::string ParserException::messageBody() const noexcept {
		return "Error during the parsing phase:\n" + specific_message_;
	}

	ParserException::ParserException(size_t line_number, std::string line, std::string specific_message) noexcept : AssemblerException(line_number, line), specific_message_(specific_message) {}
}
