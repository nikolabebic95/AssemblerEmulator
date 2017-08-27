#ifndef _symbol_definition_token_h_
#define _symbol_definition_token_h_
#include "Token.h"
#include "MicroRiscExpression.h"

namespace bnssassembler {
	
	/**
	 * \brief Class representing the symbol definition token
	 */
	class SymbolDefinitionToken : public Token {
	public:
		/**
		 * \brief Constructs a SymbolDefinitionToken object
		 * \param name Name of the symbol
		 * \param value Value of the symbol
		 * \param line_number Number of the line where the definition is located
		 * \param line Line where the definition is located
		 */
		SymbolDefinitionToken(std::string name, MicroRiscExpression value, size_t line_number, std::string line) noexcept;
		void resolveSymbolDefinitions(std::unordered_set<SymbolDefinition> symbols) noexcept override;
		void firstPass(FirstPassData &data) const override;
		void secondPass(SecondPassData &data) const override;
	private:
		std::string name_;
		MicroRiscExpression value_;
	};
}

#endif
