#ifndef _global_symbols_token_h_
#define _global_symbols_token_h_
#include "Token.h"
#include <vector>

namespace bnssassembler {
	
	/**
	 * \brief Class representing the global symbols token
	 */
	class GlobalSymbolsToken : public Token {
	public:
		/**
		 * \brief Constructs a GlobalSymbolsToken object
		 * \param symbols Vector of global symbols
		 * \param line_number Number of the line where the symbols are defined
		 * \param line Line where symbols are defined
		 */
		GlobalSymbolsToken(std::vector<std::string> symbols, size_t line_number, std::string line) noexcept;

		void firstPass(FirstPassData &data) const override;
		void secondPass(SecondPassData &data) const override;
	private:
		std::vector<std::string> symbols_;
	};
}

#endif
