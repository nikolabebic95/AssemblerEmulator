#include "ClosingBraceToken.h"
#include "MessageException.h"

namespace bnss {

	int ClosingBraceToken::inputPriority() const noexcept {
		return 1;
	}

	int ClosingBraceToken::stackPriority() const noexcept {
		return 0;
	}

	int ClosingBraceToken::rank() const noexcept {
		return 0;
	}

	std::string ClosingBraceToken::operation() const noexcept {
		return ")";
	}

	std::shared_ptr<Expression> ClosingBraceToken::create() const {
		throw MessageException("Internal error - Closing brace in postfix");
	}

	std::shared_ptr<ExpressionToken> ClosingBraceToken::clone(std::string param) const {
		return std::make_shared<ClosingBraceToken>();
	}

	bool ClosingBraceToken::isClosingBrace() const noexcept {
		return true;
	}
}
