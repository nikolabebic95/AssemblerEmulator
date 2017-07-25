#include "Immediate.h"

namespace bnss {

	Immediate::Immediate(MicroRiscExpression value) noexcept : value_(value) {}

	void Immediate::resolveSymbols(std::unordered_set<SymbolDefinition> symbols) noexcept {
		for (auto &symbol : symbols) {
			value_.setValue(symbol.name(), symbol.expression());
		}
	}

	AddressMode Immediate::addressMode() const noexcept {
		return IMMEDIATE;
	}
}
