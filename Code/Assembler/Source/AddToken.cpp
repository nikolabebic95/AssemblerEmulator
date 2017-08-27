#include "AddToken.h"
#include "AddOperation.h"

namespace bnssassembler {

	int AddToken::inputPriority() const noexcept {
		return 2;
	}

	int AddToken::stackPriority() const noexcept {
		return 2;
	}

	int AddToken::rank() const noexcept {
		return -1;
	}

	std::string AddToken::operation() const noexcept {
		return "+";
	}

	std::shared_ptr<Expression> AddToken::create() const {
		return std::make_shared<AddOperation>();
	}

	std::shared_ptr<ExpressionToken> AddToken::clone(std::string param) const {
		return std::make_shared<AddToken>();
	}
}
