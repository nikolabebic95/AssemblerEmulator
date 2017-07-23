#include "OperandParser.h"

namespace bnss {

	std::shared_ptr<Operand> OperandParser::tryParse(std::string str) const noexcept {
		auto ret = parse(str);
		if (ret != nullptr) {
			return ret;
		}

		if (next_ == nullptr) {
			return nullptr;
		}

		return next_->tryParse(str);
	}

	void OperandParser::next(std::shared_ptr<OperandParser> next) noexcept {
		next_ = next;
	}
}