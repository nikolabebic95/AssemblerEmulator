#include "MemoryDirect.h"

namespace bnss {

	MemoryDirect::MemoryDirect(MicroRiscExpression address) noexcept : address_(address) {}

	void MemoryDirect::resolveSymbols(std::unordered_set<SymbolDefinition> symbols) noexcept {
		for (auto &symbol : symbols) {
			address_.setValue(symbol.name(), symbol.expression());
		}
	}

	AddressMode MemoryDirect::addressMode() const noexcept {
		return MEMORY_DIRECT;
	}
}
