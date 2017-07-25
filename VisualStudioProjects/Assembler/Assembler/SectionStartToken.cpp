#include "SectionStartToken.h"

namespace bnss {

	SectionStartToken::SectionStartToken(SectionType type, size_t line_number, std::string line) noexcept : Token(line_number, line), type_(type) {}

	SectionStartToken::SectionStartToken(SectionType type, size_t line_number, std::string line, size_t index) noexcept : Token(line_number, line), type_(type), indexed_(true), index_(index) {}

	void SectionStartToken::firstPass(FirstPassData &data) const {
		if (indexed_) {
			data.insertSection(type_, index_);
		}
		else {
			data.insertSection(type_);
		}
	}
}
