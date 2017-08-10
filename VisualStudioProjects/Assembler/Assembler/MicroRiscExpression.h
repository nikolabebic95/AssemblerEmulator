#ifndef _micro_risc_expression_h_
#define _micro_risc_expression_h_
#include <memory>
#include "Expression.h"

namespace bnssassembler {
	
	/**
	 * \brief Adapter class for Expression
	 */
	class MicroRiscExpression {
	public:
		/**
		 * \brief Constructs a MicroRiscExpression object
		 * \param expression Pointer to Expression object that this object will adapt
		 */
		explicit MicroRiscExpression(std::shared_ptr<Expression> expression) noexcept;

		/**
		 * \brief Get the value of the expression
		 * \return Value of the expression
		 * \throw Throws if the value can not be calculated
		 */
		int32_t value() const;

		/**
		 * \brief Sets the value for the symbol
		 * \param name Name of the symbol
		 * \param expression Expression of the symbol
		 */
		bool setValue(std::string name, MicroRiscExpression expression) const noexcept;

		/**
		 * \brief Resolves the symbols from the symbol table and sets the relocation info
		 * \param symbol_table Symbol table
		 */
		void resolveSymbolTable(const SymbolTable &symbol_table) const noexcept;

		/**
		* \brief Resolves the imported symbols and sets the relocation info
		* \param imported_symbols Collection of imported symbols
		*/
		void resolveImports(std::unordered_set<std::string> imported_symbols) const noexcept;

		/**
		* \brief Resolves the current PC symbol and sets the relocation info
		* \param section_index Current PC section
		* \param offset PC address in relation to the current section beginning
		*/
		void resolveCurrentPcSymbol(size_t section_index, size_t offset) const noexcept;

		/**
		 * \brief Validates the tree and generates the relocation records for the expression
		 * \return Collection of relocation records
		 */
		std::list<RelocationRecord> generateRelocations() const;
	private:
		std::shared_ptr<Expression> expression_;
	};
}

#endif
