#include "SymbolDefinition.h"

namespace bnss {

	SymbolDefinition::SymbolDefinition(std::string name, MicroRiscExpression expression) noexcept : name_(name), expression_(expression) {}

	std::string SymbolDefinition::name() const noexcept {
		return name_;
	}

	MicroRiscExpression SymbolDefinition::expression() const noexcept {
		return expression_;
	}

	bool operator==(const SymbolDefinition &lhs, const SymbolDefinition &rhs) {
		return lhs.name_ == rhs.name_;
	}

	bool operator!=(const SymbolDefinition &lhs, const SymbolDefinition &rhs) {
		return !(lhs == rhs);
	}

	bool operator<(const SymbolDefinition &lhs, const SymbolDefinition &rhs) {
		return lhs.name_ < rhs.name_;
	}

	bool operator>(const SymbolDefinition &lhs, const SymbolDefinition &rhs) {
		return !(lhs < rhs || lhs == rhs);
	}

	bool operator<=(const SymbolDefinition &lhs, const SymbolDefinition &rhs) {
		return !(lhs > rhs);
	}

	bool operator>=(const SymbolDefinition &lhs, const SymbolDefinition &rhs) {
		return !(lhs < rhs);
	}
}
