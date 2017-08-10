#include "DivideToken.h"
#include "DivideOperation.h"

namespace bnssassembler {

	int DivideToken::inputPriority() const noexcept {
		return 3;
	}

	int DivideToken::stackPriority() const noexcept {
		return 3;
	}

	int DivideToken::rank() const noexcept {
		return 3;
	}

	std::string DivideToken::operation() const noexcept {
		return "/";
	}

	std::shared_ptr<Expression> DivideToken::create() const {
		return std::make_shared<DivideOperation>();
	}

	std::shared_ptr<ExpressionToken> DivideToken::clone(std::string param) const {
		return std::make_shared<DivideToken>();
	}
}
