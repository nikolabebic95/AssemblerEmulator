#include "Symbol.h"
#include "NonExistingSymbolException.h"

namespace bnss {
	Symbol::Symbol(std::string name) noexcept : name_(name) {}

	int32_t Symbol::value() const {
		if (assigned_) {
			return value_->value();
		}

		if (relocatable_) {
			return relocatable_value_;
		}

		throw NonExistingSymbolException(name_);
	}

	bool Symbol::setValue(std::string symbol, std::shared_ptr<Expression> value) noexcept {
		if (symbol == name_) {
			value_ = value;
			assigned_ = true;
			return true;
		}

		return false;
	}

	bool Symbol::containsSymbol() const noexcept {
		if (relocatable_) {
			return true;
		}

		if (assigned_) {
			return value_->containsSymbol();
		}

		return false;
	}

	int Symbol::symbolCount() const noexcept {
		if (relocatable_) {
			return 1;
		}
		
		if (assigned_) {
			return value_->symbolCount();
		}

		return 0;
	}

	void Symbol::resolveSymbolTable(const SymbolTable &symbol_table) noexcept {
		if (symbol_table.contains(name_)) {
			auto symbol_entry = symbol_table.at(name_);
			relocatable_value_ = static_cast<int32_t>(symbol_entry.offset());
			relocatable_ = true;
			section_index_ = symbol_entry.sectionIndex();
			absolute_ = true;
			section_ = true;
		}
		else if (assigned_) {
			value_->resolveSymbolTable(symbol_table);
		}
	}

	void Symbol::resolveImports(std::unordered_set<std::string> imported_symbols) noexcept {
		if (imported_symbols.count(name_) > 0) {
			relocatable_value_ = static_cast<int32_t>(0);
			relocatable_ = true;
			absolute_ = true;
			section_ = false;
		}
		else if (assigned_) {
			value_->resolveImports(imported_symbols);
		}
	}

	std::list<RelocationRecord> Symbol::generateRelocations() const {
		if (relocatable_) {
			if (section_) {
				return std::list<RelocationRecord> { RelocationRecord(absolute_, section_index_) };
			}
			
			return std::list<RelocationRecord> { RelocationRecord(absolute_, name_) };
		}

		return std::list<RelocationRecord>();
	}
}
