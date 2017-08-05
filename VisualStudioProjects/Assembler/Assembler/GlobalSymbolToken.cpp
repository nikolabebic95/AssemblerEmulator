#include "GlobalSymbolToken.h"
#include "SecondPassData.h"

namespace bnss {

	GlobalSymbolsToken::GlobalSymbolsToken(std::vector<std::string> symbols, size_t line_number, std::string line) noexcept : Token(line_number, line), symbols_(symbols) {}

	void GlobalSymbolsToken::firstPass(FirstPassData &data) const {
		// Do nothing
	}

	void GlobalSymbolsToken::secondPass(SecondPassData & data) const {
		for (const auto &symbol : symbols_) {
			if (data.contains(symbol)) {
				data.exportSymbol(symbol);
			}
			else {
				data.insertImported(symbol);
			}
		}
	}
}
