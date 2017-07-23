#include "Symbol.h"
#include "NonExistingSymbolException.h"

namespace bnss {
	Symbol::Symbol(std::string name) noexcept : name_(name) {}

	int32_t Symbol::value() const {
		if (assigned_) {
			return value_;
		}

		throw NonExistingSymbolException(name_);
	}

	bool Symbol::setValue(std::string symbol, int32_t value) noexcept {
		if (symbol == name_) {
			value_ = value;
			assigned_ = true;
			return true;
		}

		return false;
	}

	int Symbol::symbolCount() const noexcept {
		return 1;
	}
}