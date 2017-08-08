#include "MicroRiscExpression.h"
#include "MessageException.h"

namespace bnss {

	MicroRiscExpression::MicroRiscExpression(std::shared_ptr<Expression> expression) noexcept : expression_(expression) {}

	int32_t MicroRiscExpression::value() const {
		return expression_->value();
	}

	bool MicroRiscExpression::setValue(std::string name, MicroRiscExpression expression) const noexcept {
		return expression_->setValue(name, expression.expression_);
	}

	void MicroRiscExpression::resolveSymbolTable(const SymbolTable &symbol_table) const noexcept {
		expression_->resolveSymbolTable(symbol_table);
	}

	void MicroRiscExpression::resolveImports(std::unordered_set<std::string> imported_symbols) const noexcept {
		expression_->resolveImports(imported_symbols);
	}

	void MicroRiscExpression::resolveCurrentPcSymbol(size_t section_index, size_t offset) const noexcept {
		expression_->resolveCurrentPcSymbol(section_index, offset);
	}

	std::list<RelocationRecord> MicroRiscExpression::generateRelocations() const {
		expression_->validate();
		auto ret = expression_->generateRelocations();
		for (auto &element : ret) {
			if (element.opposite()) {
				throw MessageException((element.section() ? "Symbols from " + std::to_string(element.sectionIndex()) + "th section are " : "Symbol " + element.symbolName() + " is ") + "subtracted more times than added");
			}
		}

		return ret;
	}
}
