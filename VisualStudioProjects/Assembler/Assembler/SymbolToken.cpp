#include "SymbolToken.h"
#include "Symbol.h"
#include <climits>

namespace bnssassembler {

	SymbolToken::SymbolToken(std::string name) noexcept : name_(name) {}

	void SymbolToken::process(std::list<std::shared_ptr<ExpressionToken>>& output, std::stack<std::shared_ptr<ExpressionToken>>& stack, int & expression_rank) const {
		output.push_back(std::make_shared<SymbolToken>(*this));
		expression_rank += rank();
	}

	std::shared_ptr<Expression> SymbolToken::create() const {
		return std::make_shared<Symbol>(name_);
	}

	std::shared_ptr<ExpressionToken> SymbolToken::clone(std::string param) const {
		return std::make_shared<SymbolToken>(param);
	}

	int SymbolToken::inputPriority() const noexcept {
		return INT_MAX;
	}

	int SymbolToken::stackPriority() const noexcept {
		return INT_MAX;
	}

	int SymbolToken::rank() const noexcept {
		return 1;
	}
}
