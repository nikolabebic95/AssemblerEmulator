#include "LabelToken.h"

namespace bnss {

	LabelToken::LabelToken(std::string label, size_t line_number, std::string line) noexcept : Token(line_number, line), label_(label) {}

	void LabelToken::firstPass(FirstPassData &data) const {
		data.insertSymbol(label_);
	}

	void LabelToken::secondPass(SecondPassData &data) const {
		// Do nothing
	}
}
