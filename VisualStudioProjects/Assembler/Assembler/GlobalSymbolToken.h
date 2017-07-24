#ifndef _global_symbols_token_h_
#define _global_symbols_token_h_
#include "Token.h"
#include <vector>

namespace bnss {
	
	class GlobalSymbolsToken : public Token {
	public:
		GlobalSymbolsToken(std::vector<std::string> symbols, size_t line_number, std::string line) noexcept;
	private:
		std::vector<std::string> symbols_;
	};
}

#endif
