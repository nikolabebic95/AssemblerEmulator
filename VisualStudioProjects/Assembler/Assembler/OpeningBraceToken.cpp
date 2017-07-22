#include "OpeningBraceToken.h"
#include "MessageException.h"
#include <climits>

namespace bnss {

	int OpeningBraceToken::inputPriority() const noexcept {
		return INT_MAX - 1;
	}

	int OpeningBraceToken::stackPriority() const noexcept {
		return 0;
	}

	int OpeningBraceToken::rank() const noexcept {
		return 0;
	}

	std::string OpeningBraceToken::operation() const noexcept {
		return "(";
	}

	std::shared_ptr<Expression> OpeningBraceToken::create() const {
		throw MessageException("Error - opening brace without closing brace");
	}

	std::shared_ptr<ExpressionToken> OpeningBraceToken::clone(std::string param) const {
		return std::make_shared<OpeningBraceToken>();
	}
}
