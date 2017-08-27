#include "MultiplyToken.h"
#include "MultiplyOperation.h"

namespace bnssassembler {

	int MultiplyToken::inputPriority() const noexcept {
		return 3;
	}

	int MultiplyToken::stackPriority() const noexcept {
		return 3;
	}

	int MultiplyToken::rank() const noexcept {
		return -1;
	}

	std::string MultiplyToken::operation() const noexcept {
		return "*";
	}

	std::shared_ptr<Expression> MultiplyToken::create() const {
		return std::make_shared<MultiplyOperation>();
	}

	std::shared_ptr<ExpressionToken> MultiplyToken::clone(std::string param) const {
		return std::make_shared<MultiplyToken>();
	}
}
