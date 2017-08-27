#include "LiteralToken.h"
#include "StringHelper.h"
#include "Literal.h"
// ReSharper disable once CppUnusedIncludeDirective
#include <climits>

namespace bnssassembler {
	LiteralToken::LiteralToken(std::string value) {
		value_ = StringHelper::parseNumber<int32_t>(value);
	}

	void LiteralToken::process(std::list<std::shared_ptr<ExpressionToken>>& output, std::stack<std::shared_ptr<ExpressionToken>>& stack, int &expression_rank) const {
		output.push_back(std::make_shared<LiteralToken>(*this));
		expression_rank += rank();
	}

	std::shared_ptr<Expression> LiteralToken::create() const {
		return std::make_shared<Literal>(value_);
	}

	std::shared_ptr<ExpressionToken> LiteralToken::clone(std::string param) const {
		return std::make_shared<LiteralToken>(param);
	}

	int LiteralToken::inputPriority() const noexcept {
		return INT_MAX;
	}

	int LiteralToken::stackPriority() const noexcept {
		return INT_MAX;
	}

	int LiteralToken::rank() const noexcept {
		return 1;
	}
}
