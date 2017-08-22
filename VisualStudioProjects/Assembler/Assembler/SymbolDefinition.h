#ifndef _symbol_definition_h_
#define _symbol_definition_h_
#include "MicroRiscExpression.h"

namespace bnssassembler {
	
	/**
	 * \brief Class representing a symbol definition
	 */
	class SymbolDefinition {
	public:
		/**
		 * \brief Constructs a symbol definition
		 * \param name Name of the symbol
		 * \param expression Expression representing the symbol
		 */
		SymbolDefinition(std::string name, MicroRiscExpression expression) noexcept;

		/**
		 * \brief Get the name of the symbol
		 * \return Name of the symbol
		 */
		std::string name() const noexcept;

		/**
		 * \brief Get the expression
		 * \return Expression
		 */
		MicroRiscExpression expression() const noexcept;

		// Operator overloads:
		friend bool operator==(const SymbolDefinition &lhs, const SymbolDefinition &rhs);
		friend bool operator!=(const SymbolDefinition &lhs, const SymbolDefinition &rhs);

		friend bool operator<(const SymbolDefinition &lhs, const SymbolDefinition &rhs);
		friend bool operator>(const SymbolDefinition &lhs, const SymbolDefinition &rhs);
		friend bool operator<=(const SymbolDefinition &lhs, const SymbolDefinition &rhs);
		friend bool operator>=(const SymbolDefinition &lhs, const SymbolDefinition &rhs);
		
	private:
		std::string name_;
		MicroRiscExpression expression_;
	};
}

namespace std {
	template <> struct hash<bnssassembler::SymbolDefinition> {
		size_t operator()(const bnssassembler::SymbolDefinition & symbol) const;
	};

	inline size_t hash<bnssassembler::SymbolDefinition>::operator()(const bnssassembler::SymbolDefinition & symbol) const {
		return hash<string>()(symbol.name());
	}
}

#endif
