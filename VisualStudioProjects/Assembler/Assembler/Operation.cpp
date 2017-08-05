#include "Operation.h"

namespace bnss {
	int32_t Operation::value() const {
		return calculate(left_->value(), right_->value());
	}

	bool Operation::setValue(std::string symbol, std::shared_ptr<Expression> value) noexcept {
		return left_->setValue(symbol, value) || right_->setValue(symbol, value);
 	}

	void Operation::left(std::shared_ptr<Expression> left) noexcept {
		left_ = left;
	}

	void Operation::right(std::shared_ptr<Expression> right) noexcept {
		right_ = right;
	}

	std::shared_ptr<Expression> Operation::left() const noexcept {
		return left_;
	}

	std::shared_ptr<Expression> Operation::right() const noexcept {
		return right_;
	}

	bool Operation::containsSymbol() const noexcept {
		return left_->containsSymbol() || right_->containsSymbol();
	}

	int Operation::symbolCount() const noexcept {
		return left_->symbolCount() + right_->symbolCount();
	}

	void Operation::pushChildren(std::stack<std::reference_wrapper<std::shared_ptr<Expression>>> &stack) const noexcept {
		stack.push(const_cast<std::shared_ptr<Expression>&>(left_));
		stack.push(const_cast<std::shared_ptr<Expression>&>(right_));
	}

	void Operation::resolveSymbolTable(const SymbolTable &symbol_table) noexcept {
		left_->resolveSymbolTable(symbol_table);
		right_->resolveSymbolTable(symbol_table);
	}

	void Operation::resolveImports(std::unordered_set<std::string> imported_symbols) noexcept {
		left_->resolveImports(imported_symbols);
		right_->resolveImports(imported_symbols);
	}

	std::list<RelocationRecord> Operation::generateRelocations() const {
		auto left = left_->generateRelocations();
		auto right = right_->generateRelocations();
		left.splice(left.end(), move(right));
		return left;
	}
}
