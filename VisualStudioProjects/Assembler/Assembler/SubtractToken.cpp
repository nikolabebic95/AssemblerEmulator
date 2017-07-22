#include "SubtractToken.h"
#include "SubtractOperation.h"

namespace bnss {

	int SubtractToken::inputPriority() const noexcept {
		return 2;
	}

	int SubtractToken::stackPriority() const noexcept {
		return 2;
	}

	int SubtractToken::rank() const noexcept {
		return -1;
	}

	std::string SubtractToken::operation() const noexcept {
		return "-";
	}

	std::shared_ptr<Expression> SubtractToken::create() const {
		return std::make_shared<SubtractOperation>();
	}

	std::shared_ptr<ExpressionToken> SubtractToken::clone(std::string param) const {
		return std::make_shared<SubtractToken>();
	}
}
