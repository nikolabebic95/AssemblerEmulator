#include "FirstPassException.h"

namespace bnssassembler {

	FirstPassException::FirstPassException(size_t line_number, std::string line, std::string specific_message) noexcept : AssemblerException(line_number, line), specific_message_(specific_message) {}

	std::string FirstPassException::messageBody() const noexcept {
		return "Error during the first pass\n" + specific_message_;
	}
}
