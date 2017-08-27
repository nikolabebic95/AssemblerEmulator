#include "LineParser.h"

namespace bnssassembler {

	std::shared_ptr<Token> LineParser::tryParse(const std::string & line, size_t line_number, std::string initial_line) const {
		auto ret = parse(line, line_number, initial_line);
		if (ret != nullptr) {
			return ret;
		}

		if (next_ == nullptr) {
			return nullptr;
		}

		return next_->tryParse(line, line_number, initial_line);
	}

	void LineParser::next(std::shared_ptr<LineParser> next) noexcept {
		next_ = next;
	}
}
