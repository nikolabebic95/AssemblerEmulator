#include "SymbolTable.h"
#include "SymbolData.h"

namespace bnss {

	SymbolTable &SymbolTable::operator+=(const SymbolData & data) {
		insert(make_pair(data.name(), data));
		return *this;
	}

	bool SymbolTable::contains(std::string symbol) const noexcept {
		return count(symbol) > 0;
	}

	void SymbolTable::exportSymbol(std::string symbol) noexcept {
		(*this)[symbol].exportSymbol();
	}
}
