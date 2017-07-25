#include "Operand.h"
#include <unordered_set>

namespace bnss {

	// ReSharper disable once CppMemberFunctionMayBeStatic
	// ReSharper disable once CppMemberFunctionMayBeConst
	void Operand::resolveSymbols(std::unordered_set<SymbolDefinition> symbols) noexcept {
		// Default: Do nothing
	}
}
