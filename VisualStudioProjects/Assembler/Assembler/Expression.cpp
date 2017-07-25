#include "Expression.h"

namespace bnss {
	bool Expression::setValue(std::string symbol, std::shared_ptr<Expression> value) noexcept {
		return false;
	}

	bool Expression::validate() const noexcept {
		return true;
	}

	bool Expression::containsSymbol() const noexcept {
		return false;
	}

	int Expression::symbolCount() const noexcept {
		return 0;
	}

	void Expression::pushChildren(std::stack<std::reference_wrapper<std::shared_ptr<Expression>>> &stack) const noexcept {}
}
