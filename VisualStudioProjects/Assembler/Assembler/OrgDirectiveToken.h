#ifndef _org_directive_token_h_
#define _org_directive_token_h_
#include "Token.h"
#include "MicroRiscExpression.h"

namespace bnssassembler {
	
	/**
	 * \brief Class representing the origin directive token
	 */
	class OrgDirectiveToken : public Token {
	public:
		/**
		 * \brief Constructs an OrgDirectiveToken object
		 * \param expression Expression of this origin directive
		 * \param line_number Number of the line where this directive is located
		 * \param line Line where this directive is located
		 */
		OrgDirectiveToken(MicroRiscExpression expression, size_t line_number, std::string line) noexcept;

		void resolveSymbolDefinitions(std::unordered_set<SymbolDefinition> symbols) noexcept override;
		void firstPass(FirstPassData &data) const override;
		void secondPass(SecondPassData &data) const override;
		void resolveSymbolTable(const SymbolTable &symbol_table) noexcept override;
		void resolveImports(std::unordered_set<std::string> imported_symbols) noexcept override;
	private:
		MicroRiscExpression expression_;
	};
}

#endif
