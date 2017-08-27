#include "AssemblerException.h"
#include "StringHelper.h"

namespace bnssassembler {

	AssemblerException::AssemblerException(size_t line_number, std::string line) noexcept : line_number_(line_number), line_(line) {}

	std::string AssemblerException::message() const noexcept {
		return
			"Error in line " + StringHelper::numberFormat(line_number_) + "\n" +
			line_ + "\n" +
			messageBody();
	}

	const char *AssemblerException::what() const noexcept {
		return message().c_str();
	}
}
