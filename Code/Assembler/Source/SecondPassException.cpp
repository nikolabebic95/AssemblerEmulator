#include "SecondPassException.h"

namespace bnssassembler {

	SecondPassException::SecondPassException(size_t line_number, std::string line, std::string specific_message) noexcept : AssemblerException(line_number, line), specific_message_(specific_message) {}

	std::string SecondPassException::messageBody() const noexcept {
		return "Error during the second pass\n" + specific_message_;
	}
}
